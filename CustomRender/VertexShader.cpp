#include "VertexShader.h"

VertexShader::VertexShader()
{
	model.Identity();
	view.Identity();
	projection.Identity();
	viewport = ViewPort(0, 0, Default_Width, Default_Height);
}

VertexShader::VertexShader(Matrix model_, Matrix view_, Matrix projection_, Matrix viewport_)
	:model(model_),view(view_),projection(projection_),viewport(view_)
{

}
