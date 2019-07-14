struct PS_INPUT
{
	float4 Diffuse		: COLOR0;
	float4 Specular		: COLOR1;
	float2 TexCoord0	: TEXCOORD0;
	float2 TexCoord1	: TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 Output		: SV_TARGET0;
};

//�`��ʒu�̌v�Z�Ɏg�p����l
cbuffer CBUFFER
{
	float2	size;		//��ʃT�C�Y
	float2	pos;		//�~�̒��S���W
	float	radius;		//�~�̔��a
	bool	set_flag;	//�N���b�N�������ۂ�
	
	float	r;
	float	g;
	float	b;
	float	a;
}


//--------------------------------------------------------------------------------------------------

bool CirclePixel( float2 p )
{
	return ((p.x - pos.x) * (p.x - pos.x) +
			(p.y - pos.y) * (p.y - pos.y) -
			(radius * radius) < 0.0001f);
}


PS_OUTPUT main( PS_INPUT psin )
{
	PS_OUTPUT psout;
	
	psout.Output.r = 0.f;
	psout.Output.g = 0.f;
	psout.Output.b = 0.f;
	psout.Output.a = 0.f;
	
	float2 p;
	p.x = round(size.x * psin.TexCoord0.x / 3.f) * 3;
	p.y = round(size.y * psin.TexCoord0.y / 3.f) * 3;
	
	if(set_flag)
	{
		if(CirclePixel(p))
		{
			psout.Output.r = r;
			psout.Output.g = g;
			psout.Output.b = b;
			psout.Output.a = a;
		}
	}
	else
	{
		if(!CirclePixel(p))
		{
			psout.Output.r = r;
			psout.Output.g = g;
			psout.Output.b = b;
			psout.Output.a = a;
		}
	}
	
	return psout;
}