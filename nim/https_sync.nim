import net
import strformat
import openssl

proc SSLClientCallback(ssl: SslPtr; hint: cstring; identity: cstring; 
    max_identity_len: cuint; psk: ptr cuchar; max_psk_len: cuint): cuint {.cdecl.} =
    echo "Client callback"
    echo identity
    return 1

proc SSLServerCallback(ssl: SslPtr; identity: cstring; psk: ptr cuchar;
                       max_psk_len: cint): cuint {.cdecl.} =
    echo "Server callback"
    echo identity
    return 1

proc SSLClientPSK(hint: string): tuple[identity: string, psk: string] =
    echo "PSK func"
    return (identity: "", psk: "")

proc SSLServerPSK(hint: string): string =
    echo "PSK func"
    return ""

proc main =
    var socket = newSocket()
    var sslCtx = newContext(protVersion = protTLSv1, verifyMode = CVerifyPeer)
    echo "Set callbacks"
    SSL_CTX_set_psk_client_callback(sslCtx.context, SSLClientCallback)
    SSL_CTX_set_psk_server_callback(sslCtx.context, SSLServerCallback)
    sslCtx.clientGetPskFunc = SSLClientPSK
    sslCtx.serverGetPskFunc = SSLServerPSK
    echo "-- OK"

    sslCtx.wrapSocket(socket)
    let host="nim-lang.org"

    echo fmt"connect to {host}"
    socket.connect(host,Port(443))

    var req = fmt"""GET / HTTP/1.1
Host: {host}:443
Connection: close

"""

    echo "send\n------------"
    echo req
    echo "------------"

    socket.send(req)

    #var certs = socket.getPeerCertificates()

    var f:File
    discard f.open("https_sync_out", fmWrite)

    while true:
        var res = socket.recv(1000)
        echo "recv " & $res
        f.write(res)
        if res.len < 1:
            break

main()