#pragma once

#include "CoreEngineAPI.h"
#include <Block_ID.h>
#include <Block_Occlusion.h>
#include <BoxCollider.h>

using namespace CoreEngineNS;

namespace BlockNS
{
	class COREENGINE_API Block
	{
	public:
		Block(ID _id = ID::Air, bool _isCollidable = false, bool _isOpaque = false);
		~Block();

		inline ID			GetID			()						{ return blockID;		}
		inline bool			IsCollidable	()						{ return isCollidable;	}
		inline bool			IsOpaque		()						{ return isOpaque;		}
		inline bool			IsDirty			()						{ return isDirty;		}
		inline Face&		GetFace			()						{ return faceToDraw;	}

		inline void			SetCollidable	(bool col)				{ isCollidable	= col;	}
		inline void			SetOpaque		(bool op)				{ isOpaque		= op;	}
		inline void			SetDirty		(bool dirt)				{ isDirty		= dirt;	}
		inline void			SetFaceToRender	(Face flag)				{ faceToDraw	= flag;	}
		inline void			SetCollider		(BoxCollider col)		{ collider		= col;	}
		inline BoxCollider	GetCollider		()						{ return collider;		}

	private:
		ID		blockID;
		Face	faceToDraw;

		bool	isCollidable;
		bool	isOpaque;
		bool	isDirty;

		BoxCollider collider;
	};
}
