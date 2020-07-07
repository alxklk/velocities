const std=@import("std");

fn go() void
{
    var i : u32=2;
    while(i<50000):(i+=1)
    {
        var comp:bool=false;
        var j:u32=2;
        while(j<i):(j+=1)
        {
            var f:f32=@intToFloat(f32,i);
            var rf:f32=f/@intToFloat(f32,j);
            var r:u32=i/j;
            var ri:u32=r;
            if(@intToFloat(f32,ri) == rf)
            {
                comp=true;
                break;
            }
        }
        if(!comp)
        {
            std.debug.warn("{} - zimple\n", .{i});
        }
    }
}

pub fn main() void
{
    go();
}
