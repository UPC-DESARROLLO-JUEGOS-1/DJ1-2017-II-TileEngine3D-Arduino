#include "Vector3.h"

const Vector3 Vector3::Zero = *(new Vector3(0, 0, 0));
const Vector3 Vector3::One = *(new Vector3(1, 1, 1));
const Vector3 Vector3::UnitX = *(new Vector3(1, 0, 0));
const Vector3 Vector3::UnitY = *(new Vector3(0, 1, 0));
const Vector3 Vector3::UnitZ = *(new Vector3(0, 0, 1));
const Vector3 Vector3::Up = *(new Vector3(0, 1, 0));
const Vector3 Vector3::Down = *(new Vector3(0, -1, 0));
const Vector3 Vector3::Right = *(new Vector3(-1, 0, 0));
const Vector3 Vector3::Left = *(new Vector3(1, 0, 0));
const Vector3 Vector3::Forward = *(new Vector3(0, 0, 1));
const Vector3 Vector3::Backward = *(new Vector3(0, 0, -1));