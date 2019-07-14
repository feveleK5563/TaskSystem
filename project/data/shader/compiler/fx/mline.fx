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
	float2	size;	//��ʃT�C�Y
	float2	p1;		//���`��J�n�ʒu
	float2	p2;		//���`��I���ʒu
	float	thick;	//���̑���
	
	float	r;
	float	g;
	float	b;
	float	a;
}


//--------------------------------------------------------------------------------------------------

int IsMLine( float2 p )
{
	float tmp;
	tmp = (p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x);
	
	return (((((p1.x < p2.x && p1.x <= p.x) || (p1.x > p2.x && p1.x >= p.x)) &&
			((p2.y < p1.y && p2.y <= p.y) || (p2.y > p1.y && p2.y >= p.y))) ||
			((p1.x == p2.x && (p1.y <= p.y && p.y <= p2.y)) || 
			(p1.y == p2.y && (p1.x <= p.x && p.x <= p2.x)))) &&
			(-thick < tmp) && (tmp < thick));
}

PS_OUTPUT main( PS_INPUT psin )
{
	PS_OUTPUT psout;
	
	float2 p;
	p.x = int(round(size.x * psin.TexCoord0.x + 0.5f) / 6.f) * 6.f;
	p.y = int(round(size.y * psin.TexCoord0.y + 0.5f) / 6.f) * 6.f;
	
	psout.Output = lerp(
		float4(0.f, 0.f, 0.f, 0.f),
		float4(r, g, b, a),
		IsMLine(p));
	
	return psout;
}