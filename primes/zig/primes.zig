const std=@import("std");

const INT:type=u32;

fn go() void
{
    const stdout = std.io.getStdOut().outStream();
    var i :INT=2;
    while(i<50000):(i+=1)
    {
        var comp:bool=false;
        var j:INT=2;
        while(j<i):(j+=1)
        {
            var f:f32=@intToFloat(f32,i);
            var rf:f32=f/@intToFloat(f32,j);
            var r:INT=i/j;
            var ri:INT=r;
            if(@intToFloat(f32,ri) == rf)
            {
                comp=true;
                break;
            }
        }
        if(!comp)
        {
            var err = stdout.print("{} - zimple\n", .{i});
        }
    }
}

pub fn main() void
{
    go();
}
