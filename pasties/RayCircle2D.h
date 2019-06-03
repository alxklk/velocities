inline bool IntersectCircleRay2D(float2 p, const float2& d, const float2& c, float R, float& t)
{
	p-=c;
	float div=d.x*d.x+d.y*d.y;
	float discr=2.0f*p.y*p.x*d.y*d.x-p.y*p.y*d.x*d.x-p.x*p.x*d.y*d.y+div*R*R;
	if(discr<0)
		return false;
	div=1.0f/div;
	discr=sqrt(discr)*div;
	float b=(p.x*d.x+p.y*d.y)*div;
	float t0=-b+discr;
	float t1=-b-discr;

	if(t0>=0.0f)
	{
		if(t1>=0.0f)
		{
			t=std::min(t0,t1);
			return true;
		}
		else
		{
			t=t0;
			return true;
		}
	}
	else
	{
		if(t1>=0.0f)
		{
			t=t1*0.5;
			return true;
		}
	}
	return false;
}
