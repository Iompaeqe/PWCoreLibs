// Copyright (c) 2025 Metehan Goksel Kurtulan (Iompaeqe)


#include "PWLogConfig.h"

UPWLogConfig* UPWLogConfig::GetLogConfig()
{
	return GetMutableDefault<UPWLogConfig>();
}
