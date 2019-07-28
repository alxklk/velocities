var cmp:longint;
var i:longint;
var j:longint;
var f:real;
var rf:real;
var ri:longint;

begin
	for i:=2 to 10 do begin
		cmp:=0;
		for j:=1 to i do begin
			f:=i;
			rf:=f/j;
			ri:=trunc(rf);
			writeln(ri,'*',j, '=' ,i,'?');
			if i=(ri*j) then begin
				cmp:=1;
				break;
			end
			writeln('next');
		end;
		if cmp=0 then
			writeln(i,' -- simple');
	end
end.