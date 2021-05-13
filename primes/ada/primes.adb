with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Primes is

begin
	for i in 1..49999 loop
		declare
			comp: Boolean;
		begin
			comp:=false;
			InternalCycle:
			for j in 2..i-1 loop
				declare
					f: Float:=Float(i);
					rf: Float:=f/Float(j);
					ri: Integer:=Integer(rf);
				begin
					if rf=Float(ri) then
						comp:=true;
						exit InternalCycle;
					end if;
				end;
			end loop InternalCycle;
			if not comp then
				Put(i, Width=>0);
				Put_Line(" -- simple");
			end if;
		end;
	end loop;
end Primes;
