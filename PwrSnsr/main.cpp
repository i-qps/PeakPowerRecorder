#include <cstdio>
#include <iostream>
#include <chrono>

#include "PwrSnsrLib.h"

#define MAXBUF 2024
int main() {
	FILE* save;
	fopen_s(&save, "test.csv", "w");
	SessionID sid;
	char name[] = "USB::0x0B5B::0xFF10::10945::BTN";
	
	int rc = PwrSnsr_init(name, &sid);
	if (rc!=0) return rc;
	
	printf("Device initialized\n");
	double temp;
	PwrSnsr_GetCurrentTemp(sid, "CH1", &temp);
	printf("Current tempreture: %f degC\n", temp);

	PwrSnsr_reset(sid);
	PwrSnsr_Clear(sid);

	int ecode;
	char buf[1024];
	PwrSnsr_GetError(sid, &ecode, 1024, buf);
	printf("%d\n", ecode);
	puts(buf);
	PwrSnsr_ResetContinuousCapture(sid);
	PwrSnsr_SetEnabled(sid, "CH1", 1);
	PwrSnsr_SetMeasBuffEnabled(sid, true);
	PwrSnsr_SetGateMode(sid, PwrSnsrMeasBuffGateBurst);
	//PwrSnsr_SetGateMode(sid, PwrSnsrMeasBuffGatePeriodic);

	PwrSnsr_SetSessionCount(sid, 0);
	PwrSnsr_SetBandwidth(sid, "CH1", PwrSnsrBandwidthHigh);
	PwrSnsr_SetStartDelay(sid, 0);
	PwrSnsr_SetEndDelay(sid, 0);
	PwrSnsr_SetStartQual(sid, 1e-6);
	PwrSnsr_SetEndQual(sid, 1e-6);
	PwrSnsr_SetFilterState(sid, "CH1", PwrSnsrFilterStateAuto);
	PwrSnsr_SetFilterTime(sid, "CH1", 1);
	PwrSnsr_SetFrequency(sid, "CH1", 9.6e9);
	PwrSnsr_SetPulseUnits(sid, "CH1", PwrSnsrPulseUnitsWatts);
	PwrSnsr_SetDistal(sid, "CH1", 90);
	PwrSnsr_SetMesial(sid, "CH1", 50);
	PwrSnsr_SetProximal(sid, "CH1", 10);
	PwrSnsr_SetTrigHoldoff(sid, 10e-6);
	PwrSnsr_SetTrigLevel(sid, -10);
	PwrSnsr_SetTrigSlope(sid, PwrSnsrTriggerSlopePositive);
	PwrSnsr_SetTrigSource(sid, PwrSnsrTriggerSourceChannel1);
	PwrSnsr_SetUnits(sid, "CH1", PwrSnsrUnitsdBm);



	PwrSnsr_SetSessionTimeout(sid, 30);


	PwrSnsrTriggerModeEnum mode = PwrSnsrTriggerModeFreerun;
	PwrSnsr_SetTrigMode(sid, mode);
	//PwrSnsr_SetPeriod(sid,0.0005);
	//PwrSnsr_SetDuration(sid, 0.0001);

	 PwrSnsr_SetStartMode(sid, PwrSnsrMeasBuffStartModeImmediate);
	
	PwrSnsr_SetInitiateContinuous(sid, 1);
	PwrSnsr_SetContinuousCapture(sid, true);
	PwrSnsrMeasBuffStopReasonEnum reason;
	PulseInfo pdata[100];
	int asize, bsize;

	//PwrSnsr_AcquireMeasurements(sid, 0.1, 100, &reason, &asize);
	PwrSnsr_StartAcquisition(sid);

	unsigned int cntBuf[MAXBUF] = {};
	float timeBuf[MAXBUF] = {};
	float durBuf[MAXBUF] = {};
	float maxBuf[MAXBUF] = {};
	float minBuf[MAXBUF] = {};
	float aveBuf[MAXBUF] = {};

	auto start = std::chrono::steady_clock::now();
	auto curr = start;
	auto fstObs = start;
	auto obs = start;
	bool fstObsFlag = false;
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(20)) {
		//for (int j = 0; j < 10; j++) printf("%f ", data[j]);
		int size;
		PwrSnsr_GetBufferedMeasurementsAvailable(sid, &size);
		//printf("%d\n", size);
		if (size < 0) continue;
		if (!fstObsFlag) {
			fstObs = std::chrono::steady_clock::now();
			fstObsFlag = true;
		}
		PwrSnsr_SetReturnCount(sid, size);

		PwrSnsr_QuerySequenceNumbers(sid, "CH1", size, cntBuf, &asize);
		PwrSnsr_QueryStartTimes(sid, "CH1", size, timeBuf, &asize);
		PwrSnsr_QueryDurations(sid, "CH1", size, durBuf, &asize);
		PwrSnsr_QueryAverageMeasurements(sid, "CH1", size, aveBuf, &asize);
		PwrSnsr_QueryMaxMeasurements(sid, "CH1", size, maxBuf, &asize);
		PwrSnsr_QueryMinMeasurements(sid, "CH1", size, minBuf, &asize);
		PwrSnsr_AdvanceReadIndex(sid);
		for (int j = 0; j < asize; j++) {
			obs = fstObs + std::chrono::microseconds(static_cast<int>(timeBuf[j]*100000));
			printf("%d,%f,%f,%f,%f,%f\n", cntBuf[j], timeBuf[j], durBuf[j], maxBuf[j], minBuf[j], aveBuf[j]);
			fprintf(save, "%d,%f,%f,%f,%f,%f\n", cntBuf[j], timeBuf[j], durBuf[j], maxBuf[j], minBuf[j], aveBuf[j]);
		}
		//printf("\n");
		
	}
	auto end = std::chrono::steady_clock::now();
	//PwrSnsr_SetMeasBuffEnabled(sid, false);
	PwrSnsr_StopAcquisition(sid);
	PwrSnsr_close(sid);
	fclose(save);
	
	
	return 0;

}