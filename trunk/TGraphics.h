#ifndef TGRAPHICS_H
#define TGRAPHICS_H


namespace org
{
	namespace toxic
	{
		namespace graphics
		{
			class TGraphics
			{
				
				public:
				TGraphics();
				~TGraphics();
				
				void Init();
				void Resize(float w,float h);
				void Draw();
				void Clear();
				
				
			};
		}
	}
}


#endif
