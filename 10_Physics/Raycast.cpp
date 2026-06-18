#include "Raycast.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"

bool Physics::Raycast(int modelHandle, Vec3 start, Vec3 end, RayHit& hit)
{
    auto result = DxLib::MV1CollCheck_Line(
        modelHandle, -1, DxConv::ToVECTOR(start), DxConv::ToVECTOR(end));

    if (result.HitFlag == 0) return false;  // Œõü‚Í“–‚½‚Á‚Ä‚¢‚È‚¢

    Vec3 hitPos = DxConv::ToVec3(result.HitPosition);
    hit.point = hitPos;
    hit.normal = DxConv::ToVec3(result.Normal).Normalized();
    hit.distance = (hitPos - start).Length();

    // Œõü‚ª“–‚½‚Á‚½
    return true;
}

bool Physics::RaycastDown(int modelHandle, Vec3 origin, float maxDistance, RayHit& hit)
{
    return Raycast(modelHandle, origin, origin - Vec3::Up() * maxDistance, hit);
}

bool Physics::RaycastUp(int modelHandle, Vec3 origin, float maxDistance, RayHit& hit)
{
    return Raycast(modelHandle, origin, origin + Vec3::Up() * maxDistance, hit);
}
