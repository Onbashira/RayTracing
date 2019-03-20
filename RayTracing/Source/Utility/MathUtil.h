#pragma once
#include "vectormath/scalar/cpp/vectormath_aos.h"
#include <cmath>
#include <assert.h>
#include <random>


typedef Vectormath::Aos::Vector3 Vector3;
typedef Vectormath::Aos::Quat Quat;

typedef Vectormath::Aos::Vector3 Color3;

namespace {
	//--------------------------------------------------------------------------------------------------
	//Constant Variables
	//--------------------------------------------------------------------------------------------------
	static constexpr float F_PI = 3.1415926535897932384626433832795f;		//	 π
	static constexpr float F_2PI = 6.283185307179586476925286766559f;		//	 2π
	static constexpr float F_1DIVPI = 0.31830988618379067153776752674503f;  //	 1/π
	static constexpr float F_PIDIV2 = 1.5707963267948966192313216916398f;   //	 π/2
	static constexpr float F_PIDIV3 = 1.0471975511965977461542144610932f;   //	 π/3
	static constexpr float F_PIDIV4 = 0.78539816339744830961566084581988f;  //	 π/4
	static constexpr float F_PIDIV6 = 0.52359877559829887307710723054658f;  //	 π/6
	static constexpr float F_EPSILON = 1.192092896e-07f;                    //	 マシンイプシロン(float)

	static constexpr double D_PI = 3.1415926535897932384626433832795;		//	 π
	static constexpr double D_2PI = 6.283185307179586476925286766559;		//	 2π
	static constexpr double D_1DVIPI = 0.31830988618379067153776752674503;	//	 1/π
	static constexpr double D_PIDIV2 = 1.5707963267948966192313216916398;	//	 π/2
	static constexpr double D_PIDIV3 = 1.0471975511965977461542144610932;	//	 π/3
	static constexpr double D_PIDIV4 = 0.78539816339744830961566084581988;	//	 π/4
	static constexpr double D_PIDIV6 = 0.52359877559829887307710723054658;	//	 π/6
	static constexpr double D_EPSILON = 2.2204460492503131e-016;			//	 マシンイプシロン(double)

	static constexpr float ONB_EPSILON = 0.01f;                             // 正規直交規定を算出する際に用いるイプシロン値

	static constexpr float RECIP_PI = F_1DIVPI;
	static constexpr float RECIP_PI2 = 0.15915494f;
	static constexpr float LOG2 = 1.442695f;
	static constexpr float GAMMA_FACTOR = 2.2f;

	struct Random {
	public:
		std::random_device dev;
		std::mt19937 engine;
		std::uniform_real_distribution<double> dist;
		Random() {};
		Random(int randomSeed) {
			engine.seed(randomSeed);
			dist.reset();
		};
	public:
		static Random& get() {
			static Random random;
				return random;
		}
		double GetRand() { return dist(engine)/dist.max(); }

	};



	//二つの値から大きい値を求める
	template< typename T >inline T Max(const T& a, const T& b)
	{
		return (a > b) ? a : b;
	};

	//二つの値から小さい値を求める
	template< typename T >inline T Min(const T& a, const T& b)
	{
		return (a < b) ? a : b;
	};

	//値を最大値と最小値の範囲内にクランピングする
	template< typename T >inline T Clamp(const T& value, const T& mini, const T& maxi)
	{
		return Max(mini, Min(maxi, value));
	};

	//与えられた値を0～1に制限する
	template< typename T >inline T Saturate(const T& value)
	{
		return Clamp(value, static_cast<T>(0), static_cast<T>(1));
	};

	//符号付かどうかを判定
	template< typename T >inline T Sign(const T& value) {
		return (value < static_cast<T>(0)) ? static_cast<T>(-1) : static_cast<T>(1);
	};

	inline float pow2(float x) { return x * x; }

	inline double pow2(double x) { return x * x; }

	inline float pow3(float x) { return x * x*x; }

	inline double pow3(double x) { return x * x*x; }

	inline float pow4(float x) { return x * x*x*x; }

	inline double pow4(double x) { return x * x*x*x; }

	inline float pow5(float x) { return x * x*x*x*x; }

	inline double pow5(double x) { return x * x*x*x*x; }

	inline float clamp(float x, float a, float b) { return x < a ? a : x > b ? b : x; }

	inline double clamp(double x, double a, double b) { return x < a ? a : x > b ? b : x; }

	inline float saturate(float x) { return x < 0.f ? 0.f : x > 1.f ? 1.f : x; }

	inline double saturate(double x) { return x < 0.f ? 0.f : x > 1.f ? 1.f : x; }

	inline float recip(float x) { return 1.f / x; }

	inline double recip(double x) { return 1.f / x; }

	inline float mix(float a, float b, float t) { return a * (1.f - t) + b * t; /* return a + (b-a) * t; */ }

	inline double mix(double a, double b, double t) { return a * (1.f - t) + b * t; /* return a + (b-a) * t; */ }

	inline float step(float edge, float x) { return (x < edge) ? 0.f : 1.f; }

	inline double step(double edge, double x) { return (x < edge) ? 0.f : 1.f; }

	inline float smoothstep(float a, float b, float t) { if (a >= b) return 0.f; float x = saturate((t - a) / (b - a)); return x * x*(3.f - 2.f * t); }

	inline double smoothstep(double a, double b, double t) { if (a >= b) return 0.0; double x = saturate((t - a) / (b - a)); return x * x*(3.0 - 2.0 * t); }

	inline float radians(float deg) { return (deg / 180.f)*F_PI; }

	inline double radians(double deg) { return (deg / 180.0)*D_PI; }

	inline float degrees(float rad) { return (rad / F_PI) * 180.f; }

	inline double degrees(double rad) { return (rad / D_PI) * 180.0; }

	inline float drand48() {
		//Random& r = Random::get();
		//return float(r.GetRand()); /* RAND_MAX = 32767 */

		return float(((double)(rand()) / (RAND_MAX))); /* RAND_MAX = 32767 */
	}

	inline Vector3 random_vector() {
		return Vector3(drand48(), drand48(), drand48());
	}

	inline Vector3 random_in_unit_sphere() {
		Vector3 p;
		do {
			p = 2.f * random_vector() - Vector3(1.f);
		} while (lengthSqr(p) >= 1.f);
		return p;
	}

	inline Vector3 random_cosine_direction() {
		float r1 = drand48();
		float r2 = drand48();
		float z = sqrt(1.f - r2);
		float phi = F_2PI * r1;
		float x = cos(phi) * sqrt(r2);
		float y = sin(phi) * sqrt(r2);
		return Vector3(x, y, z);
	}

	inline Vector3 random_to_sphere(float radius, float distance_squared) {
		float r1 = drand48();
		float r2 = drand48();
		float rr = std::min(pow2(radius), distance_squared);
		float cos_theta_max = sqrtf(1.f - rr * recip(distance_squared));
		float z = 1.0f - r2 * (1.0f - cos_theta_max);
		float sqrtz = sqrtf(1.f - pow2(z));
		float phi = F_2PI * r1;
		float x = cosf(phi) * sqrtz;
		float y = sinf(phi) * sqrtz;
		return Vector3(x, y, z);
	}

	inline Vector3 linear_to_gamma(const Vector3& v, float gammaFactor) {
		float recipGammaFactor = recip(gammaFactor);
		return Vector3(
			powf(v.getX(), recipGammaFactor),
			powf(v.getY(), recipGammaFactor),
			powf(v.getZ(), recipGammaFactor));
	}

	inline Vector3 gamma_to_linear(const Vector3& v, float gammaFactor) {
		return Vector3(
			powf(v.getX(), gammaFactor),
			powf(v.getY(), gammaFactor),
			powf(v.getZ(), gammaFactor));
	}

	inline Vector3 reflect(const Vector3& v, const Vector3& n) {
		return v - 2.f * dot(v, n)*n;
	}

	inline bool refract(const Vector3& v, const Vector3& n, float ni_over_nt, Vector3& refracted) {
		Vector3 uv = normalize(v);
		float dt = dot(uv, n);
		float D = 1.f - pow2(ni_over_nt) * (1.f - pow2(dt));
		if (D > 0.f) {
			refracted = -ni_over_nt * (uv - n * dt) - n * sqrt(D);
			return true;
		}
		else {
			return false;
		}
	}

	inline float schlick(float cosine, float ri) {
		float r0 = pow2((1.f - ri) / (1.f + ri));
		return r0 + (1.f - r0) * pow5(1.f - cosine);
	}

	inline void get_sphere_uv(const Vector3& p, float& u, float& v) {
		float phi = atan2(p.getZ(), p.getX());
		float theta = asin(p.getY());
		u = 1.f - (phi + F_PI) / (2.f * F_PI);
		v = (theta + F_PI / 2.f) / F_PI;
	}

	//角度変換　度→ラジアン
	inline float DegToRad(float deg)
	{
		return deg * (F_PI / 180.f);
	};
	//角度変換　度→ラジアン
	inline float RadToDeg(float rad) {
		return rad * (180.f / F_PI);
	}

	//値がゼロであるかどうか
	inline bool IsZero(float value) {
		return fabs(value) <= F_EPSILON;
	}
	inline bool IsZero(double value) {
		return abs(value) <= D_EPSILON;
	}

	//値が等価かどうか
	inline bool IsEqual(float a, float b) {
		return fabs(a - b) <= F_EPSILON;
	}
	inline bool IsEqual(double a, double b) {
		return abs(a - b) <= D_EPSILON;
	}

	//非数かどうか
	inline bool IsNan(float value) {
		return (value != value);
	}

	//無限大かどうか
	inline bool IsInf(float value)
	{
		unsigned int f = *reinterpret_cast<unsigned int*>(&value);
		if (((f & 0x7e000000) == 0x7e000000) && (value == value))
		{
			return true;
		}
		return false;
	}

	//階乗
	unsigned int Fact(unsigned int value)
	{
		unsigned int result = 1;
		for (unsigned int i = 1; i <= value; ++i)
		{
			result *= i;
		}
		return result;
	}

	//二重階乗
	unsigned int DoubleFact(unsigned int value)
	{
		unsigned int result = 1;
		unsigned int start = ((value % 2) == 0) ? 2 : 1;
		for (unsigned int i = start; i <= value; i += 2)
		{
			result *= i;
		}
		return result;
	}



	//二項係数
	float Binormal(unsigned int n, unsigned int k)
	{
		return static_cast<float>(Fact(n) / (Fact(k)*(Fact(n - k))));
	}	
	
	//バーンスタイン
	float Bernstein(unsigned int n, unsigned int i, float t)
	{
		return static_cast<float>(Binormal(n, i)*std::powf(t, static_cast<float>(i))*std::powf(1.0f - t, static_cast<float>(n - i)));
	}

	//順列
	unsigned int Perm(unsigned int n, unsigned int r)
	{
		assert(n >= r);
		return Fact(n) / Fact(n - r);
	}
	//組み合わせ
	unsigned int Comb(unsigned int n, unsigned int r)
	{
		assert(n >= r);
		return Fact(n) / (Fact(n - r) * Fact(r));
	}

	//ちょっと早いSQRT
	float		QuickSqrt(float value)
	{

		union {
			float f;
			unsigned int i;
		}conv;

		float x2 = 0;
		float threehalf = 1.5f;

		x2 = value * 0.5f;
		conv.f = value;
		conv.i = 0x5f3759f - (conv.i >> 1);
		conv.f = conv.f*(threehalf - x2 * (conv.f * conv.f));

		return conv.f;
	}

	//フレネル項
	float		Fresnel(float n1, float n2, float cosTheta)
	{
		auto a = n1 + n2;
		auto b = n1 - n2;
		auto R = (a * a) / (b * b);
		return R + (1.0f - R) * powf(1.0f - cosTheta, 5.0f);
	}
	double		Fresnel(double n1, double n2, double cosTheta)
	{
		auto a = n1 + n2;
		auto b = n1 - n2;
		auto R = (a * a) / (b * b);
		return R + (1.0 - R) * pow(1.0f - cosTheta, 5.0);
	}


	//線形補間
	float		Lerp(float a, float b, float amount)
	{
		return a - amount * (a - b);
	}
	double		Lerp(double a, double b, double amount)
	{
		return a - amount * (a - b);
	}

	//正規直行基底
	class ONB {
	public:
		ONB() {}
		inline Vector3& operator[](int i) {
			return _axis[i];
		}
		inline const Vector3& operator[](int i) const {
			return _axis[i];
		}
		const Vector3& u() const {
			return _axis[0];
		}
		const Vector3& v() const {
			return _axis[1];
		}
		const Vector3& w() const {
			return _axis[2];
		}
		Vector3 local(float a, float b, float c) const {
			return a * u() + b * v() + c * w();
		}
		Vector3 local(const Vector3& a) const {
			return a.getX()*u() + a.getY()*v() + a.getZ()*w();
		}
		void build_from_w(const Vector3& n) {
			_axis[2] = normalize(n);
			Vector3 a;
			if (fabs(w().getX()) > 0.9) {
				a = Vector3(0, 1, 0);
			}
			else {
				a = Vector3(1, 0, 0);
			}
			_axis[1] = normalize(cross(w(), a));
			_axis[0] = cross(w(), v());
		}

	private:
		Vector3 _axis[3];
	};

}


