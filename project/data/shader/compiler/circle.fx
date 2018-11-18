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

//描画位置の計算に使用する値
cbuffer CBUFFER : register( b0 )
{
	float2	size;		//画面サイズ
	float2	pos;		//円の中心座標
	float	radius;		//円の半径
	bool	onClick;	//クリックしたか否か
}


//--------------------------------------------------------------------------------------------------

bool CirclePixel( float2 p )
{
	return ((p.x - pos.x) * (p.x - pos.x) +
			(p.y - pos.y) * (p.y - pos.y) -
			(radius * radius) < 0.000001f);
}


PS_OUTPUT main( PS_INPUT psin )
{
	PS_OUTPUT psout;
	
	psout.Output.r = 0.f;
	psout.Output.g = 0.f;
	psout.Output.b = 0.f;
	psout.Output.a = 1.f;
	
	float2 p;
	p.x = size.x * psin.TexCoord0.x;
	p.y = size.y * psin.TexCoord0.y;
	
	if(onClick)
	{
		if(CirclePixel(p))
		{
			psout.Output.r = 1.f;
		}
		else
		{
			psout.Output.r = 0.f;
		}
	}
	else
	{
		if(CirclePixel(p))
		{
			psout.Output.r = 0.f;
		}
		else
		{
			psout.Output.r = 1.f;
		}
	}
	
	return psout;
}