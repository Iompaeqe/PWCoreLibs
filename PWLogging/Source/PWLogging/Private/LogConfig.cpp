// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)


#include "LogConfig.h"

ULogConfig* ULogConfig::GetLogConfig()
{
	return GetMutableDefault<ULogConfig>();
}
