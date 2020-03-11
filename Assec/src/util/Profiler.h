#pragma once
#include "acpch.h"

namespace assec::util
{
	class Profiler
	{
	public:
		struct ProfileResult
		{
			std::string m_Name;
			long long m_Start, m_End;
		};
		struct ProfilerSession
		{
			std::string m_Name;
		};
		static Profiler& getProfiler() { static Profiler s_Instance; return s_Instance; }
		~Profiler() {}
		Profiler(Profiler const&) = delete;
		void operator=(Profiler const&) = delete;
		void beginSession(const std::string& name, const std::string& filepath = "profling_results.json")
		{
			this->m_OutputStream.open(filepath);
			this->writeHeader();
			this->m_CurrentSession = new ProfilerSession{ name };
		}
		void endSession()
		{
			this->writeFooter();
			this->m_OutputStream.close();
			delete this->m_CurrentSession;
			this->m_CurrentSession = nullptr;
			this->m_ProfileCount = 0;
		}
		void writeProfile(const ProfileResult& result)
		{
			if (this->m_ProfileCount++ > 0)
				this->m_OutputStream << ",";

			std::string name = result.m_Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			this->m_OutputStream << "{";
			this->m_OutputStream << "\"cat\":\"function\",";
			this->m_OutputStream << "\"dur\":" << (result.m_End - result.m_Start) << ',';
			this->m_OutputStream << "\"name\":\"" << name << "\",";
			this->m_OutputStream << "\"ph\":\"X\",";
			this->m_OutputStream << "\"pid\":0,";
			this->m_OutputStream << "\"tid\":0,";
			this->m_OutputStream << "\"ts\":" << result.m_Start;
			this->m_OutputStream << "}";
			this->m_OutputStream.flush();
		}
		void writeHeader()
		{
			this->m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			this->m_OutputStream.flush();
		}
		void writeFooter()
		{
			this->m_OutputStream << "]}";
			this->m_OutputStream.flush();
		}
	private:
		Profiler() : m_CurrentSession(nullptr), m_ProfileCount(0) {}
		ProfilerSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	};
	class Timer
	{
	public:
		Timer(const char* name) : m_Name(name), m_Stopped(false)
		{
			this->m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}
		~Timer()
		{
			if (!this->m_Stopped)
				this->stop();
		}
	private:
		void stop()
		{
			auto m_EndTimePoint = std::chrono::high_resolution_clock::now();
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(this->m_StartTimePoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_EndTimePoint).time_since_epoch().count();

			Profiler::getProfiler().writeProfile({ this->m_Name, start, end });

			this->m_Stopped = true;
		}
		const char* m_Name;
		bool m_Stopped;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
	};
}