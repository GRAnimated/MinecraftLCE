#include "net/minecraft/world/phys/Vec3.h"

#include "cmath"
#include "net/minecraft/core/Vec3i.h"
#include "net/minecraft/world/phys/AABB.h"

DEFINE_THREAD_STORAGE(Vec3, 1024)

Vec3* Vec3::ZERO;  // name guessed

// name guessed
void Vec3::staticCtor() {
    ZERO = new Vec3(0.0, 0.0, 0.0);
}

Vec3* Vec3::newPermanent(double x, double y, double z) {
    return new Vec3(x, y, z);
}

// name guessed
Vec3* Vec3::newPermanent(const Vec3* other) {
    return new Vec3(other->m_x, other->m_y, other->m_z);
}

Vec3* Vec3::newTemp(double x, double y, double z) {
    ThreadStorage* ts = static_cast<ThreadStorage*>(TlsGetValue(sThreadStorageIndex));
    Vec3* temp = ts->m_storage[ts->m_unk].set(x, y, z);
    ts->m_unk++;
    ts->m_unk &= 0x3ff;
    return temp;
}

// name guessed
Vec3* Vec3::newTemp(const Vec3* other) {
    return newTemp(other->m_x, other->m_y, other->m_z);
}

// name guessed
Vec3* Vec3::newTemp(const Vec3i& other) {
    return newTemp(other.getX(), other.getY(), other.getZ());
}

Vec3* Vec3::normalize() {
    double magnitude = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    if (magnitude < 0.0001)
        return newTemp(ZERO);
    return newTemp(m_x / magnitude, m_y / magnitude, m_z / magnitude);
}

// name guessed
Vec3* Vec3::lerp(Vec3* other, double weight) {
    return newTemp(m_x + (other->m_x - m_x) * weight, m_y + (other->m_y - m_y) * weight,
                   m_z + (other->m_z - m_z) * weight);
}

// name guessed
Vec3* Vec3::vectorTo(Vec3* other) {
    return newTemp(other->m_x - m_x, other->m_y - m_y, other->m_z - m_z);
}

// name guessed
Vec3* Vec3::cross(Vec3* other) {
    return newTemp(m_y * other->m_z - m_z * other->m_y, m_z * other->m_x - other->m_z * m_x,
                   other->m_y * m_x - m_y * other->m_x);
}

// name guessed
Vec3* Vec3::add(Vec3* other) {
    return add(other->m_x, other->m_y, other->m_z);
}

// name guessed
double Vec3::distanceTo(Vec3* other) {
    double dx = other->m_x - m_x;
    double dy = other->m_y - m_y;
    double dz = other->m_z - m_z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// name guessed
Vec3* Vec3::scale(double multiplier) {
    return newTemp(m_x * multiplier, m_y * multiplier, m_z * multiplier);
}

// name guessed
double Vec3::lengthSqr() {
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

// name guessed
Vec3* Vec3::getIntermediateWithXValue(Vec3* other, double x) {
    double dx = other->m_x - m_x;
    double dy = other->m_y - m_y;
    double dz = other->m_z - m_z;
    if (dx * dx < double(1.0e-7f))
        return nullptr;
    double weight = (x - m_x) / dx;
    // Reject out-of-range weights; unordered comparisons fall through in the binary.
    if (weight < 0.0 || weight > 1.0)
        return nullptr;
    return newTemp(m_x + dx * weight, m_y + weight * dy, m_z + weight * dz);
}

// name guessed
Vec3* Vec3::getIntermediateWithYValue(Vec3* other, double y) {
    double dx = other->m_x - m_x;
    double dy = other->m_y - m_y;
    double dz = other->m_z - m_z;
    if (dy * dy < double(1.0e-7f))
        return nullptr;
    double weight = (y - m_y) / dy;
    if (weight < 0.0 || weight > 1.0)
        return nullptr;
    return newTemp(m_x + dx * weight, m_y + dy * weight, m_z + weight * dz);
}

// name guessed
Vec3* Vec3::getIntermediateWithZValue(Vec3* other, double z) {
    double dx = other->m_x - m_x;
    double dy = other->m_y - m_y;
    double dz = other->m_z - m_z;
    if (dz * dz < double(1.0e-7f))
        return nullptr;
    double weight = (z - m_z) / dz;
    if (weight < 0.0 || weight > 1.0)
        return nullptr;
    return newTemp(m_x + dx * weight, m_y + dy * weight, m_z + dz * weight);
}

// name guessed
bool Vec3::equals(Vec3* other) {
    if (other->m_x != m_x)
        return false;
    if (other->m_y != m_y)
        return false;
    return other->m_z == m_z;
}

Vec3* Vec3::xRot(float angle) {
    double cosine = cosf(angle);
    double sine = sinf(angle);
    return newTemp(m_x, cosine * m_y + sine * m_z, cosine * m_z - sine * m_y);
}

Vec3* Vec3::yRot(float angle) {
    double cosine = cosf(angle);
    double sine = sinf(angle);
    return newTemp(cosine * m_x + sine * m_z, m_y, cosine * m_z - m_x * sine);
}

// name guessed
Vec3* Vec3::zRot(float angle) {
    double cosine = cosf(angle);
    double sine = sinf(angle);
    return newTemp(cosine * m_x + sine * m_y, cosine * m_y - m_x * sine, m_z);
}

Vec3* Vec3::add(double x, double y, double z) {
    return newTemp(this->m_x + x, this->m_y + y, this->m_z + z);
}

Vec3* Vec3::subtract(double x, double y, double z) {
    return add(-x, -y, -z);
}

Vec3* Vec3::subtract(Vec3* other) {
    return subtract(other->m_x, other->m_y, other->m_z);
}

double Vec3::distanceToSqr(Vec3* other) {
    double dx = other->m_x - this->m_x;
    double dy = other->m_y - this->m_y;
    double dz = other->m_z - this->m_z;
    return dx * dx + dy * dy + dz * dz;
}

double Vec3::dot(Vec3* rhs) {
    return this->m_x * rhs->m_x + this->m_y * rhs->m_y + this->m_z * rhs->m_z;
}

double Vec3::length() {
    return sqrt(this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z);
}

Vec3* Vec3::set(double x, double y, double z) {
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    return this;
}

void Vec3::resetPool() {}

double Vec3::distanceTo(AABB* aabb) {
    if (aabb->contains(this))
        return 0.0;

    double dX = 0.0;
    double dY = 0.0;
    double dZ = 0.0;

    if (this->m_x < aabb->m_inX)
        dX = aabb->m_inX - this->m_x;
    else if (this->m_x > aabb->m_axX)
        dX = this->m_x - aabb->m_axX;

    if (this->m_y < aabb->m_inY)
        dY = aabb->m_inY - this->m_y;
    else if (this->m_y > aabb->m_axY)
        dY = this->m_y - aabb->m_axY;

    if (this->m_z < aabb->m_inZ)
        dZ = aabb->m_inZ - this->m_z;
    else if (this->m_z > aabb->m_axZ)
        dZ = this->m_z - aabb->m_axZ;

    return std::sqrt(dX * dX + dY * dY + dZ * dZ);
}

Vec3* Vec3::closestPointOnSegment(Vec3* segStart, Vec3* segEnd) {
    Vec3* v1 = newTemp(this->m_x - segStart->m_x, this->m_y - segStart->m_y, this->m_z - segStart->m_z);
    Vec3* v2 = newTemp(segEnd->m_x - segStart->m_x, segEnd->m_y - segStart->m_y, segEnd->m_z - segStart->m_z);

    double dot = v1->dot(v2);
    if (dot <= 0.0) {
        return segStart;
    }

    double len2 = v2->dot(v2);
    if (len2 <= dot)
        return segEnd;

    double t = dot / len2;
    return newTemp(segStart->m_x + t * v2->m_x, segStart->m_y + t * v2->m_y, segStart->m_z + t * v2->m_z);
}

double Vec3::distanceToSegment(Vec3* segStart, Vec3* segEnd) {
    Vec3* closest = closestPointOnSegment(segStart, segEnd);
    Vec3* diff = newTemp(this->m_x - closest->m_x, this->m_y - closest->m_y, this->m_z - closest->m_z);
    return diff->length();
}
