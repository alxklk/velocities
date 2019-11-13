import macros, tables

var gStateRelations = initTable[string, seq[string]]()
proc addRelation*(state: string, parent: string) =
    var rels = gStateRelations.getOrDefault(state)
    rels.add(parent)
    gStateRelations[state] = rels

type AppearsRelation = tuple
    child: NimNode
    parents: NimNode

proc `$`(r: AppearsRelation): string =
    result = "\nrel(\tchild:" & treeRepr(r.child) & "\nparents:\t" & treeRepr(r.parents)

proc extractRelations(root: NimNode, stmtList: NimNode): Table[string, AppearsRelation]=
    var r = initTable[string, AppearsRelation]()

    for ch in stmtList.children:
        let chIdent = ch[1]
        var rel = r.getOrDefault($chIdent)
        if rel.parents.isNil:
            rel.child = chIdent
            rel.parents = newNimNode(nnkBracket)
        rel.parents.add(root)

        r[$chIdent] = rel

        if ch.len > 2 and ch[2].kind == nnkStmtList:
            var chrel = chIdent.extractRelations(ch[2])
            for k, v in chrel:
                var rel = r.getOrDefault(k)
                if rel.parents.isNil:
                    rel = v
                else:
                    for ch in v.parents:
                        if rel.parents.find(ch) == -1:
                            rel.parents.add(ch)
                r[k] = rel
    result = r

macro stateMachine*(head, body: untyped): untyped =
    var relations = head.extractRelations(body)
    result = newNimNode(nnkStmtList)

    for k, v in relations:
        let klit = newLit(k)
        for p in v.parents:
            let plit = newLit($p)
            var n = quote do:
                addRelation(`klit`, `plit`)
            result.add(n)
    #     var r = appearsAux(v.child, v.parents)
    #     result.add(r)

    echo relations
    echo "stateMachine ", $head, " :\n",  repr(result)


stateMachine test:
    - item1
    - item2
