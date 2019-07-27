#!/usr/bin/lua

for i=1,50000 do
	local comp=false
	for j=2,i-1 do
		local f=i
		local rf=f/j
		local r=math.floor(i/j)
		local ri=r
		if ri==rf then
			comp=true
			break
		end
	end
	if not comp then io.write(i,' -- lumple\n') end
end
