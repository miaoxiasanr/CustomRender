#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "CustomVector.h"
#include "CustomColor.h"

const int Default_Width = 800;
const int Default_Height = 600;
const float SCREEN_FAR = 100.f;
const float SCREEN_NEAR = 0.1f;
const vector3f DefaultLightColor = vector3f(1.0f, 0.5f, 0.31f);
const vector3f DefaultLightPosition = vector3f(1.2f, 1.0f, 2.0f);
const vector3f DefauitObjectColor = vector3f(1.0f, 0.0f, 0.0f);
const Color DefaultBGColor = Color(0.4f, 0.4f, 0.4f);
const vector3f DefaultCameraLocation = vector3f(0.f, 0.f, 3.f);

#define PI 3.1415926535
#endif // CONFIGURE_H
