/**@file PwrSnsrLib.h
 * File containing all user-callable functions.
 */
 /******************************************************************************
  *
  * Copyright 2014-19 WTG. All rights reserved.
  *
  *****************************************************************************/

  /*
   * File:   PwrSnsrLib.h
   * Author: WTG
   *
   * Created on September 19, 2014, 3:32 PM
   * 4/3/2017 Updated to match current functionality of the Windows API.
   * 4/25/2017 Updated function descriptions.
   * 9/5/2018 Bug fix for advanced measurement buffer functions.
   * 11/20/2018 Ported to Windows
   * 5/10/2018 Added simulation channels.
   */

#ifndef PWRSNSRLIB_H
#define PWRSNSRLIB_H
/**
* Successful operation return value.
*/
#define SUCCESS          (0L)
/**
* Value indicating to use the current timeout.
*/
#define CURRENT_TIMEOUT (-2)
/**
* DLL export declaration.
*/
#ifdef _WIN32

#  define EXPORT __declspec( dllexport )
#else
#  define EXPORT
#endif
/**
* Session identification handle.
*/
typedef int SessionID;

/**
* Instrument acquisition status.
 */
typedef enum PwrSnsrAcquisitionStatusEnum
{
	PwrSnsrAcqComplete = 1, /**< The sensor has completed the acquisition. */
	PwrSnsrAcqInProgress = 0, /**< The sensor is still acquiring data.*/
	PwrSnsrAcqStatusUnknown = -1 /**< The sensor cannot determine the status of the acquisition.*/
} PwrSnsrAcquisitionStatusEnum;

/**
 * Trigger mode for synchronizing data acquisition with pulsed signals.
 */
typedef enum PwrSnsrTriggerModeEnum
{
	PwrSnsrTriggerModeNormal = 1, /**< The power meter causes a sweep to be triggered each time the power level crosses the preset trigger level in the direction specified by the slope.*/
	PwrSnsrTriggerModeAuto = 2, /**<  The power meter automatically triggers if the configured trigger does not occur within the meter's timeout period. */
	PwrSnsrTriggerModeAutoLevel = 3, /**< The power meter automatically adjusts the trigger level the trigger level to halfway between the highest and lowest power levels detected.*/
	PwrSnsrTriggerModeFreerun = 4 /**The power meter forces traces at a high rate to assist in locating the signal. */
} PwrSnsrTriggerModeEnum;

/**Values for edge trigger slope*/
typedef enum PwrSnsrTriggerSlopeEnum
{
	PwrSnsrTriggerSlopePositive = 1, /**< A negative (falling) edge passing through the trigger level triggers the power meter.*/
	PwrSnsrTriggerSlopeNegative = 0/**< A positive (rising) edge passing through the trigger level triggers the power meter.*/
} PwrSnsrTriggerSlopeEnum;

/**Set or return the position of the trigger event on displayed sweep.*/
typedef enum PwrSnsrTriggerPositionEnum
{
	PwrSnsrTriggerPositionLeft = 0, /**< Left trigger position.*/
	PwrSnsrTriggerPositionMiddle = 1, /**< Middle trigger position.*/
	PwrSnsrTriggerPositionRight = 2/**< Right trigger position.*/
} PwrSnsrTriggerPositionEnum;

/**Trigger source used for synchronizing data acquisition.*/
typedef enum PwrSnsrTriggerSourceEnum
{
	PwrSnsrTriggerSourceChannel1 = 0, /**< Channel 1*/
	PwrSnsrTriggerSourceExternal = 2, /**< EXT setting uses the signal applied to the rear MULTI I/O connector.*/
	PwrSnsrTriggerSourceChannel2 = 1, /**< Channel 2*/
	PwrSnsrTriggerSourceChannel3 = 3, /**< Channel 3*/
	PwrSnsrTriggerSourceChannel4 = 4, /**< Channel 4*/
	PwrSnsrTriggerSourceChannel5 = 5, /**< Channel 5*/
	PwrSnsrTriggerSourceChannel6 = 6, /**< Channel 6*/
	PwrSnsrTriggerSourceChannel7 = 7, /**< Channel 7*/
	PwrSnsrTriggerSourceChannel8 = 8, /**< Channel 8*/
	PwrSnsrTriggerSourceChannel9 = 9, /**< Channel 9*/
	PwrSnsrTriggerSourceChannel10 = 10, /**< Channel 10*/
	PwrSnsrTriggerSourceChannel11 = 11, /**< Channel 11*/
	PwrSnsrTriggerSourceChannel12 = 12, /**< Channel 12*/
	PwrSnsrTriggerSourceChannel13 = 13, /**< Channel 13*/
	PwrSnsrTriggerSourceChannel14 = 14, /**< Channel 14*/
	PwrSnsrTriggerSourceChannel15 = 15, /**< Channel 15*/
	PwrSnsrTriggerSourceChannel16 = 16, /**< Channel 16*/
	PwrSnsrTriggerSourceIndependent = 17/**< Sets each sensor in a measurment group to use its own internal trigger.*/
} PwrSnsrTriggerSourceEnum;


/**Units returned by channel measurements.*/
typedef enum PwrSnsrUnitsEnum
{
	PwrSnsrUnitsdBm = 0, /**< dBm*/
	PwrSnsrUnitswatts = 1, /**< Watts*/
	PwrSnsrUnitsvolts = 2, /**< Volts*/
	PwrSnsrUnitsDBV = 3, /**< dBV*/
	PwrSnsrUnitsDBMV = 4, /**< dBmV*/
	PwrSnsrUnitsDBUV = 5/**< dBuV*/
} PwrSnsrUnitsEnum;

/**Marker number enumeration.*/
typedef enum PwrSnsrMarkerNumberEnum
{
	PwrSnsrMarkerNumberMarker1 = 1, /**< Marker 1*/
	PwrSnsrMarkerNumberMarker2 = 2/**< Marker2*/
} PwrSnsrMarkerNumberEnum;

/**Video bandwidth enumeration.*/
typedef enum PwrSnsrBandwidthEnum
{
	PwrSnsrBandwidthHigh = 0, /**< High bandwidth.*/
	PwrSnsrBandwidthLow = 1/**< Low bandwidth.*/
} PwrSnsrBandwidthEnum;

/** Filter state enum.*/
typedef enum PwrSnsrFilterStateEnum
{
	PwrSnsrFilterStateOff = 0, /**< Filter off.*/
	PwrSnsrFilterStateOn = 1, /**< Filter on.*/
	PwrSnsrFilterStateAuto = 2 /**< Automatically calculated filter.*/
} PwrSnsrFilterStateEnum;

/**Enum for pulse calculation units.*/
typedef enum PwrSnsrPulseUnitsEnum
{
	PwrSnsrPulseUnitsWatts = 0, /**< Calculates distal, mesial, and proximal using watts.*/
	PwrSnsrPulseUnitsVolts = 1/**< Calculates distal, mesial, and proximal using volts.*/
} PwrSnsrPulseUnitsEnum;

/**Condition code indicating validity of the measurement.*/
typedef enum PwrSnsrCondCodeEnum
{
	PwrSnsrCondCodeMeasurementStopped = -1, /**< Measurement is STOPPED. Value returned is not updated.*/
	PwrSnsrCondCodeError = 0, /**< Error return. Measurement is not valid.*/
	PwrSnsrCondCodeUnderrange = 2, /**< An Over-range condition exists.*/
	PwrSnsrCondCodeOverrange = 3, /**< An Under-range condition exists.*/
	PwrSnsrCondCodeNormal = 1/**< Normal return. No error.*/
} PwrSnsrCondCodeEnum;

/**Trigger status of the acquisition system.*/
typedef enum PwrSnsrTriggerStatusEnum
{
	PwrSnsrTriggerStatusStopped = 0, /**< Acquision is stopped.*/
	PwrSnsrTriggerStatusPretrig = 1, /**< Aquiring data and waiting for the pre-trigger to be satisfied.*/
	PwrSnsrTriggerStatusWaiting = 2, /**< Meter is armed and waiting for trigger event.*/
	PwrSnsrTriggerStatusAcquiringNew = 3, /**< Acquiring new data.*/
	PwrSnsrTriggerStatusAutoTrig = 4, /**< Meter is autotriggering.*/
	PwrSnsrTriggerStatusFreerun = 5, /**< Trigger is in free-run mode.*/
	PwrSnsrTriggerStatusTriggered = 6, /**< Meter is currently triggered.*/
	PwrSnsrTriggerStatusRunning = 7/**< Acquisition is running.*/
} PwrSnsrTriggerStatusEnum;

/**Select the action to take when either the statistical terminalcount is reached or the terminal time has elapsed.*/
typedef enum PwrSnsrTermActionEnum
{
	PwrSnsrTermActionStop = 0, /**< Stop accumulating samples and hold the result.*/
	PwrSnsrTermActionRestart = 1, /**< Clear the CCDF and begin a new one.*/
	PwrSnsrTermActionDecimate = 2/**< Divide all sample bins by 2 and continue.*/
} PwrSnsrTermActionEnum;

/**Trigger holdoff mode.*/
typedef enum PwrSnsrHoldoffModeEnum
{
	PwrSnsrHoldoffModeNormal = 1, /**< Trigger will not arm again after the trigger conditions and its inverse are satisfied and then the amount of time set for trigger holdoff.*/
	PwrSnsrHoldoffModeGap = 2/**< Trigger will not arm again after the trigger conditions are satisfied and then the amount of time set for trigger holdoff.*/
} PwrSnsrHoldoffModeEnum;

/**Gating value for statistical capture.*/
typedef enum PwrSnsrStatGatingEnum
{
	PwrSnsrStatGatingFreeRun = 0, /**< No gating.*/
	PwrSnsrStatGatingMarkers = 1/**< Gating is constrained to the portion of the the trace between the markers.*/
} PwrSnsrStatGatingEnum;

/**Multi IO trigger out modes.**/
typedef enum PwrSnsrTrigOutModeEnum
{
	PwrSnsrTrigOutModeMioOff = 0,
	PwrSnsrTrigOutModeMioPullUp = 1,
	PwrSnsrTrigOutModeMioTtl0 = 2,
	PwrSnsrTrigOutModeMioTbRef = 3,
	PwrSnsrTrigOutModeMioSweepHigh = 4,
	PwrSnsrTrigOutModeMioSweepLow = 5,
	PwrSnsrTrigOutModeMioTrigHigh = 6,
	PwrSnsrTrigOutModeMioTrigLow = 7,
	PwrSnsrTrigOutModeMioMaster = 8,
	PwrSnsrTrigOutModeMioSlave = 9
} PwrSnsrTrigOutModeEnum;

/**Measurement buffer gate modes.**/
typedef enum PwrSnsrMeasBuffGateEnum
{
	PwrSnsrMeasBuffGateBurst = 0,
	PwrSnsrMeasBuffGateMarker = 1,
	PwrSnsrMeasBuffGateExtGate = 2,
	PwrSnsrMeasBuffGatePeriodic = 3,
	PwrSnsrMeasBuffGateExtTrig = 4
} PwrSnsrMeasBuffGateEnum;

/**Measurement buffer start modes.**/
typedef enum PwrSnsrMeasBuffStartModeEnum
{
	PwrSnsrMeasBuffStartModeImmediate = 1,
	PwrSnsrMeasBuffStartModeExternalEnable = 2,
	PwrSnsrMeasBuffStartModeExternalStart = 3
} PwrSnsrMeasBuffStartModeEnum;

/**Measurement buffer stop reason.**/
typedef enum PwrSnsrMeasBuffStopReasonEnum
{
	PwrSnsrMeasBuffStopReasonCountReached = 1,
	PwrSnsrMeasBuffStopReasonTimedOut = 2,
	PwrSnsrMeasBuffStopReasonBufferOverran = 3,
	PwrSnsrMeasBuffStopReasonNone = 0
} PwrSnsrMeasBuffStopReasonEnum;

/**Select the action to take when either the statistical terminalcount is reached or the terminal time has elapsed.*/
typedef enum PwrSnsrRdgsEnableFlag
{
	PwrSnsrSequenceEnable = 1,/**< Enable sequence array capture.*/
	PwrSnsrStartTimeEnable = 2,/**< Enable start time array capture.*/
	PwrSnsrDurationEnable = 4,/**< Enable duration array capture.*/
	PwrSnsrMinEnable = 8,/**< Enable min measurement array capture.*/
	PwrSnsrAvgEnable = 16,/**< Enable average measurement capture.*/
	PwrSnsrMaxEnable = 32	/**< Enable max measurement capture.*/
} PwrSnsrRdgsEnableFlag;

/**Error codes*/
typedef enum PwrSnsrErrorCodesEnum
{
	PWR_SNSR_IO_GENERAL = -2147204588, /**< I/O error.*/
	PWR_SNSR_IO_TIMEOUT = -2147204587, /**< I/O timeout error.*/
	PWR_SNSR_MODEL_NOT_SUPPORTED = -2147204586, /**< Instrument model does not support this feature.*/
	PWR_SNSR_INV_PARAMETER = -1073807240, /**< Invalid parameter value*/
	PWR_SNSR_ERROR_INVALID_SESSION_HANDLE = -1074130544, /**< Session ID invalid.*/
	PWR_SNSR_ERROR_STATUS_NOT_AVAILABLE = -1074134947, /**< Status not available.*/
	PWR_SNSR_ERROR_RESET_FAILED = -1074134945,/**< Reset failed.*/
	PWR_SNSR_ERROR_RESOURCE_UNKNOWN = -1074134944, /**< Unknown resource descriptor.*/
	PWR_SNSR_ERROR_ALREADY_INITIALIZED = -1074134943, /**< Session already initialized.*/
	PWR_SNSR_ERROR_OUT_OF_MEMORY = -1074134954, /**< Out of memory.*/
	PWR_SNSR_ERROR_OPERATION_PENDING = -1074134953, /**< Operation pending.*/
	PWR_SNSR_ERROR_NULL_POINTER = -1074134952, /**< Null pointer not allowed.*/
	PWR_SNSR_ERROR_UNEXPECTED_RESPONSE = -1074134951, /**< Unexpected response from the instrument.*/
	PWR_SNSR_ERROR_NOT_INITIALIZED = -1074135011, /**< Session not initialized.*/

	/*libusb errors*/
	/** Input/output error */
	PWR_SNSR_LIBUSB_ERROR_IO = -1,

	/** Invalid parameter */
	PWR_SNSR_LIBUSB_ERROR_INVALID_PARAM = -2,

	/** Access denied (insufficient permissions) */
	PWR_SNSR_LIBUSB_ERROR_ACCESS = -3,

	/** No such device (it may have been disconnected) */
	PWR_SNSR_LIBUSB_ERROR_NO_DEVICE = -4,

	/** Entity not found */
	PWR_SNSR_LIBUSB_ERROR_NOT_FOUND = -5,

	/** Resource busy */
	PWR_SNSR_LIBUSB_ERROR_BUSY = -6,

	/** Operation timed out */
	PWR_SNSR_LIBUSB_ERROR_TIMEOUT = -7,

	/** Overflow */
	PWR_SNSR_LIBUSB_ERROR_OVERFLOW = -8,

	/** Pipe error */
	PWR_SNSR_LIBUSB_ERROR_PIPE = -9,

	/** System call interrupted (perhaps due to signal) */
	PWR_SNSR_LIBUSB_ERROR_INTERRUPTED = -10,

	/** Insufficient memory */
	PWR_SNSR_LIBUSB_ERROR_NO_MEM = -11,

	/** Operation not supported or unimplemented on this platform */
	PWR_SNSR_LIBUSB_ERROR_NOT_SUPPORTED = -12,

	/** Other error */
	PWR_SNSR_LIBUSB_ERROR_OTHER = -99,
} PwrSnsrErrorCodesEnum;


#ifdef __cplusplus
extern "C" {
#endif


	/** @defgroup ScpiFunctions Scpi Functions
	*  SCPI command functions
	*  @{
	*/
	/**
	 * @brief Send a SCPI command to the instrument.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Command
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SendSCPICommand(SessionID Vi, const char * Command);
	/**
	 * @brief Read a SCPI string response from the instrument.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param ValueBufferSize Number of elements in Value.
	 * @param ValueActualSize Number of elements actually written to Value.
	 * @param Value The string returned from the instrument SCPI interface.
	 * @param Timeout Time out in milliseconds for the read operation. Use -1 for infinite and -2 to use the existing time out value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadSCPI(SessionID Vi, int ValueBufferSize, long * ValueActualSize, char Value[], int Timeout);

	/**
	* @brief Send a SCPI command to the instrument using a named SCPI parser.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param name Name of the parser. Creates a new parser if the name is not already used.
	* @param Command
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SendSCPIToNamedParser(SessionID Vi, const char * name, const char * Command);
	/**
	 * @brief Read a SCPI string response from the instrument.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param name Name of the parser. If parser doesn't exist, returns PWR_SNSR_ERROR_NULL_POINTER. PwrSnsr_SendSCPIToNamedParser can be used to create a named parser.
	 * @param ValueBufferSize Number of elements in Value.
	 * @param ValueActualSize Number of elements actually written to Value.
	 * @param Value The string returned from the instrument SCPI interface.
	 * @param Timeout Time out in milliseconds for the read operation. Use -1 for infinite and -2 to use the existing time out value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadSCPIFromNamedParser(SessionID Vi, const char * name, int ValueBufferSize, long * ValueActualSize, char Value[], int Timeout);

	/**
	* @brief Send a SCPI command as a byte array.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param CommandBufferSize Number of elements in Command.
	* @param Command Command to send.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SendSCPIBytes(SessionID Vi, int CommandBufferSize, char Command[]);
	/**
	 * @brief Read a SCPI byte array response from the instrument.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param ValueBufferSize Number of elements in Value.
	 * @param Value The byte array returned from the instrument SCPI interface.
	 * @param ValueActualSize
	 * @param Timeout Time out in milliseconds for the read operation. Use -1 for infinite and -2 to use the existing time out value. Time out in milliseconds for the read operation. Use -1 for infinite and -2 to use the existing time out value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadSCPIBytes(SessionID Vi, int ValueBufferSize, char Value[], long* ValueActualSize, int Timeout);

	/** @} */ // end of ScpiFunctions


	/** @defgroup SessionManagment Session Management
	*  Session management functions
	*  @{
	*/
	
	 /**
	 * @brief Returns a delimited string of available resources. These strings can be used in the initialize function to open a session to an instrument.
	 * @param Delimiter The string used to delimit the list of resources ie. "|", " ", ";", etc.
	 * @param ValBufferSize Number of elements in Val.
	 * @param Val The return string.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FindResources(const char* Delimiter, int ValBufferSize, char Val[]);
	/**
	* @brief Gets the minimum supported firmware as an integer. Format is YYYYMMDD.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetMinimumSupportedFirmware(int * Version);
	
	/**
	* @brief Sets the time out in milliseconds for I/O.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Milliseconds Time out in milliseconds. Use -1 for infinite time out.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetTimeOut(SessionID Vi, long Milliseconds);
	/**
	 * @brief Returns the time out value for I/O in milliseconds.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Val Time out in milliseconds. -1 denotes infinite time out.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTimeOut(SessionID Vi, long* Val);
	/**
	 * @brief Initialize a communication session with a supported USB power
	 * sensor.
	 * @param ResourceName Name of the resource.
	 * The resource descriptor is in the following format:<BR>
	 * USB::[VID]::[PID]::[Serial Number]::SNSR <BR>
	 * Where serial number is the USB power meter’s serial number in decimal format, <BR>
	 * and the VID and PID are in hexidecimal format. <BR>
	 * e.g. For serial number 1234, VID of 0x1bfe and PID of 0x5500:<BR>
	 * USB::0x1BFE::0x5500::1234::SNSR <BR>
	 * Multiple channel synthetic meters can be defined by combining more than one descriptor separated by a semicolon. <BR>
	 * Channel assignment is determined by the order in the list, in other words CH1 would be the first listed resource, <BR>
	 * CH2 the second resource, etc. <BR>
	 * e.g. Define a synthetic peak power meter using serial number 1234 for CH1 and serial number 4242 for CH2: <BR>
	 * USB::0x1BFE::0x5500::1234::SNSR;USB::0x1BFE::0x5500::4242::SNSR <BR>
	 * @param Vi The SessionID handle
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_init(char * ResourceName, SessionID* Vi);
	/**
	 * @brief Closes the I/O session to the instrument. Driver methods and properties that access the instrument are not accessible after Close is called.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_close(SessionID Vi);
	/**
	 * @brief This function retrieves and then clears the error information for the session. Normally, the error information describes the first error that occurred since the user last called the Get Error or Clear Error function.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param ErrorCode
	 * @param ErrorDescriptionBufferSize
	 * @param ErrorDescription
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetError(SessionID Vi, int* ErrorCode, int ErrorDescriptionBufferSize, char ErrorDescription[]);
	/**
	 * @brief This function clears the error code and error description for the given session.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ClearError(SessionID Vi);
	/**
	 * Places the instrument in a known state.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_reset(SessionID Vi);
	/**
	 * @brief Performs an instrument self test, waits for the instrument to complete the test, and queries the instrument for the results. If the instrument passes the test, TestResult is 0.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param TestResult Error or success code.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_self_test(SessionID Vi, int* TestResult);

	

	/**
	* @brief Set the period the library waits to update fetch measurements in ms.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Latency Fetch latency in ms.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetFetchLatency(SessionID Vi, int Latency);
	/**
	* @brief Get the period the library waits to update fetch measurements in ms.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Latency Fetch latency in ms.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetFetchLatency(SessionID Vi, int *Latency);
	 /** @} */ // end of SessionManagment

	/** @defgroup Measurements Measurements
	*  General measurement functions
	*  @{
	*/
	/**
	* @brief Return average power using a default instrument configuration in Modulated Mode and dBm units. Instrument remains stopped in Modulated Mode after a measurement.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.
	* @param Val Average power in dBm
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_MeasurePower(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum* CondCode, float* Val);
	/**
	 * @brief Returns the most recently acquired CW power.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val CW power in channel units.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchCWPower(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum* CondCode, float* Val);
	/**
	 * @brief Return average voltage using a default instrument configuration in Modulated Mode and volts units. Instrument remains stopped in Modulated Mode after a measurement.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val Average voltage in linear volts.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_MeasureVoltage(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum* CondCode, float* Val);

	/**
	 * @brief Initiates an acquisition on all enabled channels, waits (up to MaxTime) for the acquisition to complete, and returns the min/max waveforms for this channel. Call FetchMinMaxWaveform to obtain the min/max waveforms for other channels.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param MinWaveformBufferSize Size in bytes of the MinWaveform buffer.
	 * @param MinWaveform This array contains the min waveform. Units for the individual array elements are in the channel units setting.
	 * @param MinWaveformActualSize Size in bytes of the data written to MinWaveform.
	 * @param MaxWaveformBufferSize Size in bytes of the MaxWaveform buffer.
	 * @param MaxWaveform This array contains the max waveform. Units for the individual array elements are in the channel units setting.
	 * @param MaxWaveformActualSize Size in bytes of the data written to MaxWaveform.
	 * @param WaveformArrayBufferSize Size in bytes of the Waveform buffer.
	 * @param WaveformArray The array contains the average waveform. Units for the individual array elements are in the channel units setting.
	 * @param WaveformArrayActualSize Size in bytes of the data written to WaveformArray.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadWaveformMinMax(SessionID Vi, const char * Channel, int MinWaveformBufferSize, float MinWaveform[], int * MinWaveformActualSize, int MaxWaveformBufferSize, float MaxWaveform[], int * MaxWaveformActualSize, int WaveformArrayBufferSize, float WaveformArray[], int * WaveformArrayActualSize);
	/**
	 * @brief Initiates an acquisition on all enabled channels, waits (up to MaxTime) for the acquisition to complete, and returns the waveform for this channel. Call FetchWaveform to obtain the waveforms for other channels.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param WaveformArrayBufferSize Size in bytes of the Waveform buffer.
	 * @param WaveformArray The array contains the average waveform. Units for the individual array elements are in the channel units setting.
	 * @param WaveformArrayActualSize Size in bytes of the data written to WaveformArray.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadWaveform(SessionID Vi, const char * Channel, int WaveformArrayBufferSize, float WaveformArray[], int * WaveformArrayActualSize);

	/**
	 * @brief Returns the previously acquired minimum and maximum waveforms for this specified channel. The acquisition must be made prior to calling this method. Call this method separately for each channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param MinWaveformBufferSize Size in bytes of the MinWaveform buffer.
	 * @param MinWaveform This array contains the min waveform. Units for the individual array elements are in the channel units setting.
	 * @param MinWaveformActualSize Size in bytes of the data written to MinWaveform.
	 * @param MaxWaveformBufferSize Size in bytes of the MaxWaveform buffer.
	 * @param MaxWaveform This array contains the max waveform. Units for the individual array elements are in the channel units setting.
	 * @param MaxWaveformActualSize Size in bytes of the data written to MaxWaveform.
	 * @param WaveformArrayBufferSize Size in bytes of the Waveform buffer.
	 * @param WaveformArray The array contains the average waveform. Units for the individual array elements are in the channel units setting.
	 * @param WaveformArrayActualSize Size in bytes of the data written to WaveformArray.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchWaveformMinMax(SessionID Vi, const char * Channel, int MinWaveformBufferSize, float MinWaveform[], int * MinWaveformActualSize, int MaxWaveformBufferSize, float MaxWaveform[], int * MaxWaveformActualSize, int WaveformArrayBufferSize, float WaveformArray[], int * WaveformArrayActualSize);
	/**
	 * @brief Returns a previously acquired waveform for this channel. The acquisition must be made prior to calling this method. Call this method separately for each channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param WaveformArrayBufferSize Size in bytes of the Waveform buffer.
	 * @param WaveformArray The array contains the average waveform. Units for the individual array elements are in the channel units setting.
	 * @param WaveformArrayActualSize Size in bytes of the data written to WaveformArray.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchWaveform(SessionID Vi, const char * Channel, int WaveformArrayBufferSize, float WaveformArray[], int * WaveformArrayActualSize);
	/**
	 * @brief Returns an array of the current automatic amplitude measurements performed on <BR>
	 * a periodic pulse waveform.
	 * @details Measurements performed are: peak amplitude during <BR>
	 * the pulse, average amplitude over a full cycle of the pulse waveform, average <BR>
	 * amplitude during the pulse, IEEE top amplitude, IEEE bottom amplitude, and overshoot. <BR>
	 * Units are the same as the channel's units. <BR> <BR>
	 * Note the pulse overshoot is returned in dB for logarithmic channel units, <BR>
	 * and percent for all other units. Also, the pulse ?ON interval used for peak <BR>
	 * and average calculations is defined by the SENSe:PULSe:STARTGT and :ENDGT time gating settings. <BR>
	 * A full pulse (rise and fall) must be visible on the display to make average <BR>
	 * and peak pulse power measurements, and a full cycle of the waveform must be <BR>
	 * visible to calculate average cycle amplitude.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PulsePeak The peak amplitude during the pulse.
	 * @param PulsePeakValid Condition code.
	 * @param PulseCycleAvg Average cycle amplitude.
	 * @param PulseCycleAvgValid Condition code.
	 * @param PulseOnAvg Average power of the ON portion of the pulse.
	 * @param PulseOnValid Condition code.
	 * @param IEEETop The IEEE-defined top line, i.e. the portion of a pulse waveform, which represents the second nominal state of a pulse.
	 * @param IEEETopValid Condition code.
	 * @param IEEEBottom The IEEE-define base line, i.e. The two portions of a pulse waveform which represent the first nominal state from which a pulse departs and to which it ultimately returns.
	 * @param IEEEBottomValid Condition code.
	 * @param Overshoot The difference between the distortion following a major transition and the IEEE top line in dB or percent,depending on the channel units.
	 * @param OvershootValid Condition code.
	 * @param Droop Pulse droop.
	 * @param DroopValid Condition code.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchPowerArray(SessionID Vi, const char * Channel, float* PulsePeak, PwrSnsrCondCodeEnum * PulsePeakValid, float* PulseCycleAvg, PwrSnsrCondCodeEnum * PulseCycleAvgValid,
		float* PulseOnAvg, PwrSnsrCondCodeEnum * PulseOnValid, float* IEEETop, PwrSnsrCondCodeEnum * IEEETopValid, float* IEEEBottom, PwrSnsrCondCodeEnum * IEEEBottomValid,
		float* Overshoot, PwrSnsrCondCodeEnum * OvershootValid, float* Droop, PwrSnsrCondCodeEnum * DroopValid);

	/**
	 * @brief Returns an array of the current automatic timing measurements performed
	 * on a periodic pulse waveform.
	 * @details Measurements performed are: the frequency, period,
	 * width, offtime and duty cycle of the pulse waveform, and the risetime and falltime
	 * of the edge transitions. For each of the measurements to be performed, the
	 * appropriate items to be measured must within the trace window.
	 * Pulse frequency, period, offtime and duty cycle measurements require that an
	 * entire cycle of the pulse waveform (minimum of three edge transitions) be present.
	 * Pulse width measurement requires that at least one full pulse is visible,
	 * and is most accurate if the pulse width is at least 0.4 divisions. Risetime
	 * and falltime measurements require that the edge being measured is visible,
	 * and will be most accurate if the transition takes at least 0.1 divisions.
	 * It is always best to have the power meter set on the fastest timebase
	 * possible that meets the edge visibility restrictions. Set the trace averaging
	 * as high as practical to reduce fluctuations and noise in the pulse timing measurements.
	 * Note that the timing of the edge transitions is defined by the settings of
	 * the SENSe:PULSe:DISTal, :MESIal and :PROXimal settings; see the descriptions
	 * @brief Forthose commands. Units are the same as the channel's units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Frequency The number of cycles of a repetitive signal that take place in one second (Pulse Repetition Frequency).
	 * @param FrequencyValid Condition code.
	 * @param Period The interval between two successive pulses.
	 * @param PeriodValid Condition code.
	 * @param Width The interval between the first and second signal crossings of the mesial line.
	 * @param WidthValid Condition code.
	 * @param Offtime The time a repetitive pulse is off. (Equal to the pulse period minus the pulse width).
	 * @param OfftimeValid Condition code.
	 * @param DutyCycle The ratio of the pulse on-time to period.
	 * @param DutyCycleValid Condition code.
	 * @param Risetime The interval between the first signal crossing of the proximal line to the first signal crossing of the distal line.
	 * @param RisetimeValid Condition code.
	 * @param Falltime The interval between the last signal crossing of the distal line to the last signal crossing of the proximal line.
	 * @param FalltimeValid Condition code.
	 * @param EdgeDelay Time offset from the trigger reference to the first mesial transition level of either slope on the waveform.
	 * @param EdgeDelayValid Condition code.
	 * @param Skew The trigger offset between the assigned trigger channel and this channel.
	 * @param SkewValid Condition code.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchTimeArray(SessionID Vi, const char * Channel, float* Frequency, PwrSnsrCondCodeEnum * FrequencyValid, float* Period, PwrSnsrCondCodeEnum * PeriodValid,
		float* Width, PwrSnsrCondCodeEnum * WidthValid, float* Offtime, PwrSnsrCondCodeEnum * OfftimeValid, float* DutyCycle, PwrSnsrCondCodeEnum * DutyCycleValid,
		float* Risetime, PwrSnsrCondCodeEnum * RisetimeValid, float* Falltime, PwrSnsrCondCodeEnum * FalltimeValid, float* EdgeDelay, PwrSnsrCondCodeEnum * EdgeDelayValid,
		float* Skew, PwrSnsrCondCodeEnum * SkewValid);
	/**
	 * @brief Returns the current average, maximum, minimum powers or voltages and the <br>
	 * peak-to-average ratio of the specified channel. Units are the same as the <br>
	 * channel units. Note the peak-to-average ratio and marker ratio are returned <br>
	 * in dB for logarithmic channel units, and percent for all other channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PeakAverage Average power of the peak power envelope.
	 * @param PeakAverageValid Condition code.
	 * @param PeakMax maximum power of the peak power envelope.
	 * @param PeakMaxValid Condition code.
	 * @param PeakMin Minimum power of the peak power envelope.
	 * @param PeakMinValid Condition code.
	 * @param PeakToAvgRatio Peak to average ratio.
	 * @param PeakToAvgRatioValid Condition code.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchCWArray(SessionID Vi, const char * Channel, float* PeakAverage, PwrSnsrCondCodeEnum * PeakAverageValid,
		float* PeakMax, PwrSnsrCondCodeEnum * PeakMaxValid, float* PeakMin, PwrSnsrCondCodeEnum * PeakMinValid, 
		float* PeakToAvgRatio, PwrSnsrCondCodeEnum * PeakToAvgRatioValid);
	/**
	 * @brief Returns the interval between the first signal crossing of the proximal line to the first signal crossing of the distal line.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchRiseTime(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns the pulse width, i.e. the interval between the first and second signal crossings of the mesial line.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchWidth(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);

	/**
	 * @brief Returns the peak amplitude during the pulse.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchPulsePeak(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Average power of the ON portion of the pulse.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchPulseOnAverage(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);

	/**
	 * @brief Returns the average power of the entire pulse.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchPulseCycleAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);

	/**
	 * @brief Returns the number of cycles of a repetitive signal that take place in one second (Pulse Repetition Frequency).
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchPRF(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns the interval between two successive pulses. (Reciprocal of the Pulse RepetitionFrequency)
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchPeriod(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns the difference between the distortion following a major transition and the IEEE top line in dB or percent, depending on the channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchOvershoot(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns the time a repetitive pulse is off. (Equal to the pulse period minus the pulsewidth).
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchOfftime(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns the IEEE-defined top line, i.e. the portion of a pulse waveform which represents the second nominal state of a pulse.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIEEETop(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);

	/**
	 * @brief Returns the IEEE-define base line, i.e. The two portions of a pulse waveform which represent the first nominal state from which a pulse departs and to which it ultimately returns.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIEEEBottom(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns the interval between the last signal crossing of the distal line to the last signalcrossing of the proximal line.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchFallTime(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns time offset from the trigger reference to the first mesial transition level of either slope on the waveform.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid
	 * @param Val
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchEdgeDelay(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns the ratio of the pulse on-time to off-time.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsValid Condition code.
	 * @param Val Measurement return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchDutyCycle(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);

	/**
	* Initiates a CW power acquisition and returns the result in channel units.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param IsValid Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadCWPower(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * IsValid, float* Val);

	/**
	* @brief Returns the current average, maximum, minimum powers or voltages and the
	* peak-to-average ratio of the specified channel. Units are the same as the
	* channel's units. Note the peak-to-average ratio and marker ratio are returned
	* in dB for logarithmic channel units, and percent for all other channel units.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param PeakAverage Average power of the peak power envelope.
	* @param PeakAverageValid Condition code.
	* @param PeakMax Maximum power of the peak power envelope.
	* @param PeakMaxValid Condition code.
	* @param PeakMin Minimum power of the peak power envelope.
	* @param PeakMinValid Condition code.
	* @param PeakToAvgRatio Peak to average ratio.
	* @param PeakToAvgRatioValid Condition code.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadCWArray(SessionID Vi, const char * Channel, float* PeakAverage, PwrSnsrCondCodeEnum * PeakAverageValid, 
		float* PeakMax, PwrSnsrCondCodeEnum * PeakMaxValid, float* PeakMin, PwrSnsrCondCodeEnum * PeakMinValid, 
		float* PeakToAvgRatio, PwrSnsrCondCodeEnum * PeakToAvgRatioValid);
	/**
	* @brief Returns an array of the current automatic amplitude measurements performed on a periodic pulse waveform. <br>
	* @details Measurements performed are: peak amplitude during the pulse, average amplitude over a full cycle of the  <br>
	* pulse waveform, average amplitude during the pulse, IEEE top amplitude, IEEE bottom amplitude, and overshoot.  <br>
	* Units are the same as the channel's units. Note the pulse overshoot is returned in dB for logarithmic channel units,  <br>
	* and percent for all other units. Also, the pulse ON interval used for peak and average calculations is  <br>
	* defined by the SENSe:PULSe:STARTGT and :ENDGT time gating settings.  <br>
	* A full pulse (rise and fall) must be visible on the display to make average and peak pulse power measurements,  <br>
	* and a full cycle of the waveform must be visible to calculate average cycle amplitude.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param PulsePeak The peak amplitude during the pulse.
	* @param PulsePeakValid Condition code.
	* @param PulseCycleAvg Average cycle amplitude.
	* @param PulseCycleAvgValid Condition code.
	* @param PulseOnAvg Average power of the ON portion of the pulse.
	* @param PulseOnValid Condition code.
	* @param IEEETop The IEEE-defined top line, i.e. the portion of a pulse waveform, which represents the second nominal state of a pulse.
	* @param IEEETopValid Condition code.
	* @param IEEEBottom The IEEE-define base line, i.e. The two portions of a pulse waveform which represent the first nominal state from which a pulse departs and to which it ultimately returns.
	* @param IEEEBottomValid Condition code.
	* @param Overshoot The difference between the distortion following a major transition and the IEEE top line in dB or percent,depending on the channel units.
	* @param OvershootValid Condition code.
	* @param Droop Pulse droop.
	* @param DroopValid Condition code.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadPowerArray(SessionID Vi, const char * Channel, float* PulsePeak, PwrSnsrCondCodeEnum * PulsePeakValid, 
		float* PulseCycleAvg, PwrSnsrCondCodeEnum * PulseCycleAvgValid, float* PulseOnAvg, PwrSnsrCondCodeEnum * PulseOnValid, 
		float* IEEETop, PwrSnsrCondCodeEnum * IEEETopValid, float* IEEEBottom, PwrSnsrCondCodeEnum * IEEEBottomValid, 
		float* Overshoot, PwrSnsrCondCodeEnum * OvershootValid, float* Droop, PwrSnsrCondCodeEnum * DroopValid);
	/**
	* @brief Returns an array of the current automatic timing measurements performed on a periodic pulse waveform.
	*
	* @details Measurements performed are: the frequency, period,
	* width, offtime and duty cycle of the pulse waveform, and the risetime and falltime
	* of the edge transitions. For each of the measurements to be performed, the
	* appropriate items to be measured must within the trace window.
	* Pulse frequency, period, offtime and duty cycle measurements require that an
	* entire cycle of the pulse waveform (minimum of three edge transitions) be present.
	* Pulse width measurement requires that at least one full pulse is visible,
	* and is most accurate if the pulse width is at least 0.4 divisions. Risetime
	* and falltime measurements require that the edge being measured is visible,
	* and will be most accurate if the transition takes at least 0.1 divisions.
	* It is always best to have the power meter set on the fastest timebase
	* possible that meets the edge visibility restrictions. Set the trace averaging
	* as high as practical to reduce fluctuations and noise in the pulse timing measurements.
	* Note that the timing of the edge transitions is defined by the settings of
	* the SENSe:PULSe:DISTal, :MESIal and :PROXimal settings; see the descriptions
	* For those commands. Units are the same as the channel's units.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Frequency The number of cycles of a repetitive signal that take place in one second (Pulse Repetition Frequency).
	* @param FrequencyValid Condition code.
	* @param Period The interval between two successive pulses.
	* @param PeriodValid Condition code.
	* @param Width The interval between the first and second signal crossings of the mesial line.
	* @param WidthValid Condition code.
	* @param Offtime The time a repetitive pulse is off. (Equal to the pulse period minus the pulse width).
	* @param OfftimeValid Condition code.
	* @param DutyCycle The ratio of the pulse on-time to period.
	* @param DutyCycleValid Condition code.
	* @param Risetime The interval between the first signal crossing of the proximal line to the first signal crossing of the distal line.
	* @param RisetimeValid Condition code.
	* @param Falltime The interval between the last signal crossing of the distal line to the last signal crossing of the proximal line.
	* @param FalltimeValid Condition code.
	* @param EdgeDelay Time offset from the trigger reference to the first mesial transition level of either slope on the waveform.
	* @param EdgeDelayValid Condition code.
	* @param Skew The trigger offset between the assigned trigger channel and this channel.
	* @param SkewValid Condition code.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadTimeArray(SessionID Vi, const char * Channel, float* Frequency, PwrSnsrCondCodeEnum * FrequencyValid,
		float* Period, PwrSnsrCondCodeEnum * PeriodValid, float* Width, PwrSnsrCondCodeEnum * WidthValid, float* Offtime, 
		PwrSnsrCondCodeEnum * OfftimeValid, float* DutyCycle, PwrSnsrCondCodeEnum * DutyCycleValid, float* Risetime, 
		PwrSnsrCondCodeEnum * RisetimeValid, float* Falltime, PwrSnsrCondCodeEnum * FalltimeValid, float* EdgeDelay, 
		PwrSnsrCondCodeEnum * EdgeDelayValid, float* Skew, PwrSnsrCondCodeEnum * SkewValid);
	
	/**
	* @brief Returns the ratio of the pulse on-time to off-time.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadDutyCycle(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns time offset from the trigger reference to the first mesial transition level of either slope on the waveform.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadEdgeDelay(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the interval between the last signal crossing of the distal line to the last signal crossing of the proximal line.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadFallTime(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the IEEE-define base line, i.e. The two portions of a pulse waveform
	* which represent the first nominal state from which a pulse departs and to which it ultimately returns.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadIEEEBottom(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the IEEE-defined top line, i.e. the portion of a pulse waveform which represents the second nominal state of a pulse.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadIEEETop(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the time a repetitive pulse is off. (Equal to the pulse period minus the pulse width).
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadOfftime(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the difference between the distortion following a major transition and the IEEE top line in dB or percent, depending on the channel units.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadOvershoot(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the interval between two successive pulses.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadPeriod(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the number of cycles of a repetitive signal that take place in one second (Pulse Repetition Frequency).
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadPRF(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the average power of the entire pulse.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadPulseCycleAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Average power of the ON portion of the pulse.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadPulseOnAverage(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the peak amplitude during the pulse.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadPulsePeak(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the interval between the first signal crossing of the proximal line to the first signal crossing of the distal line.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadRiseTime(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	* @brief Returns the pulse width, i.e. the interval between the first and second signal crossings of the mesial line.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param CondCode Condition code for the measurement.  Condition code.
	* @param Val Measurement value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ReadWidth(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);

	/** @} */ // end of Measurements

	/** @defgroup Trigger Trigger
	*  Trigger related functions
	*  @{
	*/
	/**
	 * @brief Return the trigger delay time in seconds with respect to the trigger for
	 * the trigger display location in the LEFT position.
	 * @details  Positive values cause the
	 * actual trigger to occur after the trigger condition is met.
	 * This places the trigger event to the left of the trigger point on the display,
	 * and is useful for viewing events during a pulse, some fixed delay time after the
	 * rising edge trigger. Negative trigger delay places the trigger event to the
	 * right of the trigger point on the display, and is useful for looking at
	 * events before the trigger edge.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Delay
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigDelay(SessionID Vi, float* Delay);
	/**
	 * @brief Sets the trigger delay time in seconds with respect to the trigger for
	 * the trigger display location in the LEFT position.
	 * @details  Positive values cause the
	 * actual trigger to occur after the trigger condition is met.
	 * This places the trigger event to the left of the trigger point on the display,
	 * and is useful for viewing events during a pulse, some fixed delay time after the
	 * rising edge trigger. Negative trigger delay places the trigger event to the
	 * right of the trigger point on the display, and is useful for looking at
	 * events before the trigger edge.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Delay
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigDelay(SessionID Vi, float Delay);
	/**
	 * @brief Return the trigger holdoff time in seconds.
	 * @details Trigger holdoff is used
	 * to disable the trigger for a specified amount of time after each trigger event.
	 * The holdoff time starts immediately after each valid trigger edge, and will not
	 * permit any new triggers until the time has expired. When the holdoff time is up,
	 *  the trigger re-arms, and the next valid trigger event (edge) will cause a
	 * new sweep. This feature is used to help synchronize the power meter with
	 * burst waveforms such as a TDMA or GSM frame. The trigger holdoff resolution
	 * is 10 nanoseconds, and it should be set to a time that is just slightly shorter
	 * than the frame repetition interval.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Holdoff
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigHoldoff(SessionID Vi, float* Holdoff);
	/**
	 * @brief Sets the trigger holdoff time in seconds.
	 * @details Trigger holdoff is used
	 * to disable the trigger for a specified amount of time after each trigger event.
	 * The holdoff time starts immediately after each valid trigger edge, and will not
	 * permit any new triggers until the time has expired. When the holdoff time is up,
	 *  the trigger re-arms, and the next valid trigger event (edge) will cause a
	 * new sweep. This feature is used to help synchronize the power meter with
	 * burst waveforms such as a TDMA or GSM frame. The trigger holdoff resolution
	 * is 10 nanoseconds, and it should be set to a time that is just slightly shorter
	 * than the frame repetition interval.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Holdoff
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigHoldoff(SessionID Vi, float Holdoff);
	/**
	 * @brief Returns the holdoff mode to normal or gap holdoff.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param HoldoffMode holdoff mode.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigHoldoffMode(SessionID Vi, PwrSnsrHoldoffModeEnum * HoldoffMode);
	/**
	 * @brief Sets the holdoff mode to normal or gap holdoff.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param HoldoffMode Holdoff mode.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigHoldoffMode(SessionID Vi, PwrSnsrHoldoffModeEnum HoldoffMode);
	/**
	 * @brief Return the trigger level for synchronizing data acquisition
	 * with a pulsed input signal
	 * @details The internal trigger level entered should include
	 * any global offset and will also be affected by the frequency cal factor.
	 * The available internal trigger level range is sensor dependent.
	 * The trigger level is set and returned in dBm.
	 * This setting is only valid for normal and auto trigger modes.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Level Trigger level in dBm.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigLevel(SessionID Vi, float* Level);
	/**
	 * @brief Set the trigger level for synchronizing data acquisition
	 * with a pulsed input signal
	 * @details The internal trigger level entered should include
	 * any global offset and will also be affected by the frequency cal factor.
	 * The available internal trigger level range is sensor dependent.
	 * The trigger level is set and returned in dBm.
	 * This setting is only valid for normal and auto trigger modes.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Level Trigger level in dBm.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigLevel(SessionID Vi, float Level);
	/**
	 * @brief Return the trigger mode for synchronizing data acquisition with pulsed signals.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Mode Trigger mode.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigMode(SessionID Vi, PwrSnsrTriggerModeEnum * Mode);
	/**
	 * @brief Set the trigger mode for synchronizing data acquisition with pulsed signals.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Mode Trigger mode.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigMode(SessionID Vi, PwrSnsrTriggerModeEnum Mode);
	/**
	 * @brief Return the position of the trigger event on displayed sweep.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Position Trigger position.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigPosition(SessionID Vi, PwrSnsrTriggerPositionEnum * Position);
	/**
	 * @brief Set the position of the trigger event on displayed sweep.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Position Trigger position.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigPosition(SessionID Vi, PwrSnsrTriggerPositionEnum Position);
	/**
	 * @brief Set the signal the power meter monitors for a trigger. It can be channel external input, or independent.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Source
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigSource(SessionID Vi, PwrSnsrTriggerSourceEnum * Source);
	/**
	 * @brief Get the signal the power meter monitors for a trigger. It can be channel external input, or independent.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Source
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigSource(SessionID Vi, PwrSnsrTriggerSourceEnum Source);
	/**
	 * @brief The status of the triggering system. Update rate is controlled by FetchLatency setting.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Status Status of the trigger.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigStatus(SessionID Vi, PwrSnsrTriggerStatusEnum * Status);
	/**
	 * @brief Return the fine position of the trigger event on the power sweep.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Vernier Trigger position -30.0 to 30.0 (0.0 = left, 5.0 = middle, 10.0 = Right).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigVernier(SessionID Vi, float* Vernier);
	/**
	 * @brief Set the fine position of the trigger event on the power sweep.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Vernier Trigger position -30.0 to 30.0 (0.0 = left, 5.0 = middle, 10.0 = Right).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigVernier(SessionID Vi, float Vernier);
	/**
	 * @brief Return the trigger slope or polarity.
	 * @details When set to positive,
	 * trigger events will be generated when a signal rising edge crosses the trigger
	 * level threshold. When negative, trigger events are generated on the falling
	 * edge of the pulse.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Slope
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTrigSlope(SessionID Vi, PwrSnsrTriggerSlopeEnum * Slope);
	/**
	 * @brief Sets the trigger slope or polarity.
	 * @details When set to positive,
	 * trigger events will be generated when a signal rising edge crosses the trigger
	 * level threshold. When negative, trigger events are generated on the falling
	 * edge of the pulse.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Slope
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTrigSlope(SessionID Vi, PwrSnsrTriggerSlopeEnum Slope);
	/**
	* @brief Sets the trigger out/mult io mode. Setting trigger mode overrides this command.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Mode Trigger out/multi IO mode
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetTrigOutMode(SessionID Vi, const char * Channel, int Mode);

	/** @} */ // end of Trigger

	/** @defgroup Acquisition Acquisition
	*  Acquisition related functions
	*  @{
	*/

	/**
	* @brief Terminates any measurement in progress and resets the state of the trigger system.
	* Note that Abort will leave the measurement in a stopped condition with all current measurements cleared.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_Abort(SessionID Vi);

	/**
	* @brief When capture priority is enabled, returns up to 100000 points of trace data
	* based on the current timebase starting at the current trigger delay point.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param WaveformArrayBufferSize Number of elements in the WaveformArray buffer
	* @param WaveformArray Waveform buffer.
	* @param WaveformArrayActualSize Number of elements updated with data.
	* @param Count Number of points to capture.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_FetchExtendedWaveform(SessionID Vi, const char * Channel, int WaveformArrayBufferSize,
		float WaveformArray[], int* WaveformArrayActualSize, int Count);
	/**
	 * @brief Clear all data buffers. Clears averaging filters to empty.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_Clear(SessionID Vi);
	/**
	 * @brief Starts a single measurement cycle when INITiate:CONTinuous is set to OFF.
	 * @details  In Modulated Mode, the measurement will complete once the power has been
	 * integrated for the full FILTer time. In Pulse Mode, enough trace sweeps
	 * must be triggered to satisfy the AVERaging setting.
	 * In Statistical Mode, acquisition stops once the terminal condition(s) are met.
	 * In each case, no reading will be returned until the measurement is complete.
	 * This command is not valid when INITiate:CONTinuous is ON, however, by
	 * convention this situation does not result in a SCPI error
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_InitiateAquisition(SessionID Vi);
	/**
	 * @brief Returns whether an acquisition is in progress, complete, or if the status is unknown.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Val Status out parameter.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_Status(SessionID Vi, PwrSnsrAcquisitionStatusEnum * Val);
	/**
	 * @brief Set the data acquisition mode for single or free-run measurements.
	 * @details If INITiate:CONTinuous is set to ON, the instrument immediately begins taking
	 * measurements (Modulated, CW and Statistical Modes), or arms its trigger and
	 * takes a measurement each time a trigger occurs (Pulse Mode). If set to OFF,
	 * the measurement will begin (or be armed) as soon as the INITiate command is
	 * issued, and will stop once the measurement criteria (averaging, filtering or
	 * sample count) has been satisfied. Note that INITiate:IMMediate and READ commands
	 * are invalid when INITiate:CONTinuous is set to ON; however, by convention this
	 * situation does not result in a SCPI error.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param InitiateContinuous Boolean. 0 for off or 1 for on.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetInitiateContinuous(SessionID Vi, int InitiateContinuous);
	/**
	 * @brief Get the data acquisition mode for single or free-run measurements.
	 * @details If INITiate:CONTinuous is set to ON, the instrument immediately begins taking
	 * measurements (Modulated, CW and Statistical Modes), or arms its trigger and
	 * takes a measurement each time a trigger occurs (Pulse Mode). If set to OFF,
	 * the measurement will begin (or be armed) as soon as the INITiate command is
	 * issued, and will stop once the measurement criteria (averaging, filtering or
	 * sample count) has been satisfied. Note that INITiate:IMMediate and READ commands
	 * are invalid when INITiate:CONTinuous is set to ON; however, by convention this
	 * situation does not result in a SCPI error.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param InitiateContinuous Boolean. 0 for off or 1 for on.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetInitiateContinuous(SessionID Vi, int* InitiateContinuous);

	/**
	 * @brief Sets the 55 series power meter to a buffered capture mode and disables real time processing.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Enabled If set to 1, enables buffered mode. If set to zero, disables capture priority(default).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_EnableCapturePriority(SessionID Vi, const char * Channel, int Enabled);


	/** @} */ // end of Acquisition


	/** @defgroup Channel Channel Functions
	*  Channel related functions
	*  @{
	*/

	/**
	* @brief Gets the channel name by zero index. Note: SCPI commands use a one-based index.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param BuffSize Buffer size for Channel
	* @param Channel Channel number buffer
	* @param Index the index of the channel
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetChannelByIndex(SessionID Vi, int BuffSize, char Channel[], int Index);

	/**
	 * @brief Get the measurement state of the selected channel. When the value is true,
	 * the channel performs measurements; when the value is false, the channel is disabled
	 * and no measurements are performed.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Enabled Boolean. 1 for enabled; 0 for disabled.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetEnabled(SessionID Vi, const char * Channel, int* Enabled);
	/**
	 * @brief Get the measurement state of the selected channel. When the value is true,
	 * the channel performs measurements; when the value is false, the channel is disabled
	 * and no measurements are performed.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Enabled Boolean. 1 for enable; 0 for disable.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetEnabled(SessionID Vi, const char * Channel, int Enabled);
	/**
	 * @brief Gets the serial number of the sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param SerialNumberBufferSize Size in bytes of Serial number.
	 * @param SerialNumber Out parameter. ASCII string serial number.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetSerialNumber(SessionID Vi, const char * Channel, int SerialNumberBufferSize, char SerialNumber[]);

	/**
	 * @brief Get number of channels.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Count Number of channels
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetChannelCount(SessionID Vi, int * Count);

	/**
	 * @brief Get units for the selected channel.
	 * @details Voltage is calculated with
	 * reference to the sensor input impedance. Note that for ratiometric results,
	 * logarithmic units will always return dBr (dB relative) while linear units return percent.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Units
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetUnits(SessionID Vi, const char * Channel, PwrSnsrUnitsEnum * Units);
	/**
	 * @brief Set units for the selected channel.
	 * @details Voltage is calculated with
	 * reference to the sensor input impedance. Note that for ratiometric results,
	 * logarithmic units will always return dBr (dB relative) while linear units return percent.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Units
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetUnits(SessionID Vi, const char * Channel, PwrSnsrUnitsEnum Units);
	/**
	 * @brief Get current sensor internal temperature in degrees C
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CurrentTemp
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetCurrentTemp(SessionID Vi, const char * Channel, double* CurrentTemp);
	/**
	 * @brief Get the number of traces averaged together to form the measurement result on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Average
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetAverage(SessionID Vi, const char * Channel, int * Average);
	/**
	 * @brief Set the number of traces averaged together to form the measurement result on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Average
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetAverage(SessionID Vi, const char * Channel, int Average);
	/**
	 * @brief Get the sensor video bandwidth for the selected sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Bandwidth
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetBandwidth(SessionID Vi, const char * Channel, PwrSnsrBandwidthEnum * Bandwidth);
	/**
	 * @brief Set the sensor video bandwidth for the selected sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Bandwidth
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetBandwidth(SessionID Vi, const char * Channel, PwrSnsrBandwidthEnum Bandwidth);
	/**
	 * @brief Get the current setting of the integration filter on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param FilterState State of the filter.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetFilterState(SessionID Vi, const char * Channel, PwrSnsrFilterStateEnum * FilterState);
	/**
	 * @brief Set the current setting of the integration filter on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param FilterState State of the filter.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetFilterState(SessionID Vi, const char * Channel, PwrSnsrFilterStateEnum FilterState);
	/**
	 * @brief Get the current length of the integration filter on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param FilterTime Filter time in seconds.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetFilterTime(SessionID Vi, const char * Channel, float* FilterTime);
	/**
	 * @brief Set the current length of the integration filter on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param FilterTime Filter time in seconds.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetFilterTime(SessionID Vi, const char * Channel, float FilterTime);
	/**
	* @brief Retruns true if sensor is average responding (not peak detecting).
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param IsAvgSensor True if sensor is average responding.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetIsAvgSensor(SessionID Vi, const char * Channel, int* IsAvgSensor);
	/**
	 * @brief Get the pulse amplitude percentage, which is used to define the end
	 * of a rising edge or beginning of a falling edge transition.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Distal
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetDistal(SessionID Vi, const char * Channel, float* Distal);
	/**
	 * @brief Set the pulse amplitude percentage, which is used to define the end
	 * of a rising edge or beginning of a falling edge transition.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Distal
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetDistal(SessionID Vi, const char * Channel, float Distal);
	/**
	 * @brief Get the point on a pulse, which is used to define the end of the pulse's active interval.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param EndGate
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetEndGate(SessionID Vi, const char * Channel, float* EndGate);
	/**
	 * @brief Set the point on a pulse, which is used to define the end of the pulse's active interval.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param EndGate
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetEndGate(SessionID Vi, const char * Channel, float EndGate);
	/**
	 * @brief Get the pulse amplitude percentage, which is used to define the midpoint of a rising edge or end of a falling edge transition.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Mesial
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMesial(SessionID Vi, const char * Channel, float* Mesial);
	/**
	 * @brief Set the pulse amplitude percentage, which is used to define the midpoint of a rising edge or end of a falling edge transition.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Mesial
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetMesial(SessionID Vi, const char * Channel, float Mesial);
	/**
	 * @brief Get the pulse amplitude percentage, which is used to define the beginning of a rising edge or end of a falling edge transition.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Proximal
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetProximal(SessionID Vi, const char * Channel, float* Proximal);
	/**
	 * @brief Set the pulse amplitude percentage, which is used to define the beginning of a rising edge or end of a falling edge transition.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Proximal
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetProximal(SessionID Vi, const char * Channel, float Proximal);
	/**
	 * @brief Get the units for entering the pulse distal, mesial and proximal levels.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Units PwrSnsrPulseUnitsEnum Pulse calculation units (watts or volts).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetPulseUnits(SessionID Vi, const char * Channel, PwrSnsrPulseUnitsEnum * Units);
	/**
	 * @brief Set the units for entering the pulse distal, mesial and proximal levels.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PwrSnsrPulseUnitsEnum Pulse calculation units (watts or volts).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetPulseUnits(SessionID Vi, const char * Channel, PwrSnsrPulseUnitsEnum PwrSnsrPulseUnitsEnum);
	/**
	 * @brief Get the point on a pulse, which is used to define the beginning of the pulse's active interval.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param StartGate
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetStartGate(SessionID Vi, const char * Channel, float* StartGate);
	/**
	 * @brief Set the point on a pulse, which is used to define the beginning of the pulse's active interval.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param StartGate
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetStartGate(SessionID Vi, const char * Channel, float StartGate);

	/**
	* @brief Query information associated with calibration factors.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param MaxFrequency Maximum RF frequency measureable by this channel.
	* @param MinFrequency Minimum RF frequency measureable by this channel.
	* @param FrequencyListBufferSize Number of elements in FrequencyList.
	* @param FrequencyList List of frequencies correlated to the cal factors.
	* @param FrequencyListActualSize Actual number of elements returned in FrequencyList.
	* @param CalFactorListBufferSize Number of elements in CalFactorList.
	* @param CalFactorList List of cal factors correlated to the frequencies.
	* @param CalFactorListActualSize Actual number of elements returned in CalFactorList.
	* @param Bandwidth Bandwidth of interest. Cal factors for low and high bandwidth are different.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetCalFactors(SessionID Vi, const char * Channel, float* MaxFrequency, float* MinFrequency,
		int FrequencyListBufferSize, float FrequencyList[], int * FrequencyListActualSize,
		int CalFactorListBufferSize, float CalFactorList[], int * CalFactorListActualSize, PwrSnsrBandwidthEnum Bandwidth);

	/**
	 * @brief Get the frequency calibration factor currently in use on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CalFactor
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetCalFactor(SessionID Vi, const char * Channel, float* CalFactor);
	/**
	 * @brief Set the frequency calibration factor currently in use on the selected channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CalFactor
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetCalFactor(SessionID Vi, const char * Channel, float CalFactor);
	/**
	 * @brief Get the RF frequency for the current sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Frequency RF Frequency in Hz.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetFrequency(SessionID Vi, const char * Channel, float* Frequency);
	/**
	 * @brief Set the RF frequency for the current sensor, and apply the appropriate frequency calibration factor from the sensor internal table.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Frequency RF Frequency in Hz.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetFrequency(SessionID Vi, const char * Channel, float Frequency);
	/**
	 * @brief Get a measurement offset in dB for the selected sensor.
	 * @details This setting is used
	 * to compensate for external couplers, attenuators or amplifiers in the RF signal
	 * path ahead of the power sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param OffsetdB
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetOffsetdB(SessionID Vi, const char * Channel, float* OffsetdB);
	/**
	 * @brief Set a measurement offset in dB for the selected sensor.
	 * @details This setting is used
	 * to compensate for external couplers, attenuators or amplifiers in the RF signal
	 * path ahead of the power sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param OffsetdB
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetOffsetdB(SessionID Vi, const char * Channel, float OffsetdB);
	/**
	 * @brief Get the state of the peak sensor temperature compensation system.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TempComp Boolean. 1 for on; 0 for off.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTempComp(SessionID Vi, const char * Channel, int* TempComp);
	/**
	 * @brief Set the state of the peak sensor temperature compensation system.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TempComp Boolean. 1 for on; 0 for off.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTempComp(SessionID Vi, const char * Channel, int TempComp);
	/**
	* @brief Gets the model of the meter connected to the specified channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param ModelBufferSize Size of the buffer..
	* @param Model Buffer where the model is read into.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetModel(SessionID Vi, const char * Channel, int ModelBufferSize, char Model[]);

	/**
	* @brief Get the number of min/max traces averaged together to form the peak hold measurement results on the selected channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param EnvelopeAverage Out parameter value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetPeakHoldDecay(SessionID Vi, const char * Channel, int* EnvelopeAverage);

	/**
	* @brief Returns whether peak hold decay automatically tracks trace averaging. If set to true, the peak hold decay and trace averaging values are the same. If set to false, peak hold decay is indepedent.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param EnvelopeTracking Out boolean parameter value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetPeakHoldTracking(SessionID Vi, const char * Channel, int* EnvelopeTracking);
	/**
	* @brief Sets whether peak hold decay automatically tracks trace averaging. If set to true, the peak hold decay and trace averaging values are the same. If set to false, peak hold decay is indepedent.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param EnvelopeTracking Boolean value. True to set peak hold tracking on.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetPeakHoldTracking(SessionID Vi, const char * Channel, int EnvelopeTracking);
	/**
	* @brief Returns the firmware version of the power meter associated with this channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param FirmwareVersionBufferSize Size of the FirmwareVersion buffer.
	* @param FirmwareVersion Buffer to hold the firmware version.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetFirmwareVersion(SessionID Vi, const char * Channel, int FirmwareVersionBufferSize, char FirmwareVersion[]);
	/**
	* @brief Set the number of min/max traces averaged together to form the peak hold measurement results on the selected channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param PeakHoldDecay Peak hold decay value.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetPeakHoldDecay(SessionID Vi, const char * Channel, int PeakHoldDecay);
	/** @} */ // end of Channel

	/** @defgroup Time Time Base Functions
	*  Time base and span functions
	*  @{
	*/

	/**
	 * @brief Get the Pulse Mode timebase in seconds/division. (10 divisions = 1 trace)
	 * Value = 5e-9 to 10e-3 (or max timebase) sec in a 1-2-5 sequence,
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Timebase
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTimebase(SessionID Vi, float* Timebase);
	/**
	 * @brief Set the Pulse Mode timebase in seconds/division. (10 divisions = 1 trace)
	 * Value = 5e-9 to 10e-3 sec (or max timebase)  in a 1-2-5 sequence,
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Timebase
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTimebase(SessionID Vi, float Timebase);
	/**
	 * @brief Set the horizontal time span of the trace in pulse mode.
	 * Time span = 10* Time/Division.
	 * Value = 5e-8 to 100e-3 sec in a 1-2-5 sequence
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Timespan
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTimespan(SessionID Vi, float Timespan);
	/**
	 * @brief Get the horizontal time span of the trace in pulse mode.
	 * Time span = 10* Time/Division.
	 * Value = 5e-8 to 100e-3 sec in a 1-2-5 sequence
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Timespan
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTimespan(SessionID Vi, float* Timespan);
	/**
	 * @brief Gets the maximum timebase setting available.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param MaxTimebase
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMaxTimebase(SessionID Vi, float* MaxTimebase);

	/** @} */ // end of Time


	/** @defgroup Marker Marker Functions
	*  Marker functions
	*  @{
	*/

	/**
	* @brief Get the time (x-axis-position) of the selected marker relative to the trigger.
	* @details Note that time markers must be positioned within the time limits of
	* the trace window in the graph display. If a time outside of the display limits
	* is entered, the marker will be placed at the first or last time position as
	* appropriate.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param MarkerNumber
	* @param TimePosition
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetMarkerTimePosition(SessionID Vi, int MarkerNumber, float* TimePosition);
	/**
	* @brief Set the time (x-axis-position) of the selected marker relative to the trigger.
	* @details Note that time markers must be positioned within the time limits of
	* the trace window in the graph display. If a time outside of the display limits
	* is entered, the marker will be placed at the first or last time position as
	* appropriate.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param MarkerNumber
	* @param TimePosition
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetMarkerTimePosition(SessionID Vi, int MarkerNumber, float TimePosition);
	/**
	* @brief Get the horizontal pixel position (X-axis-position) of the selected vertical marker.
	* There are 501 pixel positions numbered from 0 to 500 inclusive.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param MarkerNumber
	* @param PixelPosition
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetMarkerPixelPosition(SessionID Vi, int MarkerNumber, int * PixelPosition);
	/**
	* @brief Set the horizontal pixel position (X-axis-position) of the selected vertical marker.
	* There are 501 pixel positions numbered from 0 to 500 inclusive.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param MarkerNumber
	* @param PixelPosition
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetMarkerPixelPosition(SessionID Vi, int MarkerNumber, int PixelPosition);
	/**
	 * @brief Returns an array of the current marker measurements for the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param AvgPower Average power between the markers.
	 * @param AvgPowerCondCode Condition code.
	 * @param MaxPower Maximum power between the markers.
	 * @param MaxPowerCondCode Condition code.
	 * @param MinPower Minimum power between the markers.
	 * @param MinPowerCondCode Condition code.
	 * @param PkToAvgRatio The ratio of peak to average power between the markers.
	 * @param PkToAvgRatioCondCode Condition code.
	 * @param Marker1Power The power at Marker 1.
	 * @param Marker1PowerCondCode Condition code.
	 * @param Marker2Power The power at Marker 2.
	 * @param Marker2PowerCondCode Condition code.
	 * @param MarkerRatio Ratio of power at Marker 1 and power at Marker 2.
	 * @param MarkerRatioCondCode Condition code.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchArrayMarkerPower(SessionID Vi, const char * Channel, float* AvgPower,
		PwrSnsrCondCodeEnum * AvgPowerCondCode, float* MaxPower,
		PwrSnsrCondCodeEnum * MaxPowerCondCode, float* MinPower,
		PwrSnsrCondCodeEnum * MinPowerCondCode, float* PkToAvgRatio,
		PwrSnsrCondCodeEnum * PkToAvgRatioCondCode, float* Marker1Power,
		PwrSnsrCondCodeEnum * Marker1PowerCondCode, float* Marker2Power,
		PwrSnsrCondCodeEnum * Marker2PowerCondCode, float* MarkerRatio,
		PwrSnsrCondCodeEnum * MarkerRatioCondCode);
	/**
	 * @brief Forthe specified marker, return the average power or voltage at the marker.
	 * The units are the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Marker Marker number.
	 * @param IsValid Condition code.
	 * @param Val Measurement value
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMarkerAverage(SessionID Vi, const char * Channel, int Marker, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Forthe specified marker, return the maximum power or voltage at the marker. The units are the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Marker Marker number.
	 * @param IsValid
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMarkerMax(SessionID Vi, const char * Channel, int Marker, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Forthe specified marker, return the minimum power or voltage at the marker. The units are the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Marker Marker number.
	 * @param IsValid
	 * @param Val measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMarkerMin(SessionID Vi, const char * Channel, int Marker, PwrSnsrCondCodeEnum * IsValid, float* Val);
	/**
	 * @brief Returns an array of the current marker measurements for the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param AvgPower Average power between the markers.
	 * @param AvgPowerCondCode Condition code.
	 * @param MaxPower Maximum power between the markers.
	 * @param MaxPowerCondCode Condition code.
	 * @param MinPower Minimum power between the markers.
	 * @param MinPowerCondCode Condition code.
	 * @param PkToAvgRatio The ratio of peak to average power between the markers.
	 * @param PkToAvgRatioCondCode Condition code.
	 * @param Marker1Power The power at Marker 1.
	 * @param Marker1PowerCondCode Condition code.
	 * @param Marker2Power The power at Marker 2.
	 * @param Marker2PowerCondCode Condition code.
	 * @param MarkerRatio Ratio of power at Marker 1 and power at Marker 2.
	 * @param MarkerRatioCondCode Condition code.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadArrayMarkerPower(SessionID Vi, const char * Channel, float* AvgPower, PwrSnsrCondCodeEnum * AvgPowerCondCode, float* MaxPower, PwrSnsrCondCodeEnum * MaxPowerCondCode, float* MinPower, PwrSnsrCondCodeEnum * MinPowerCondCode, float* PkToAvgRatio, PwrSnsrCondCodeEnum * PkToAvgRatioCondCode, float* Marker1Power, PwrSnsrCondCodeEnum * Marker1PowerCondCode, float* Marker2Power, PwrSnsrCondCodeEnum * Marker2PowerCondCode, float* MarkerRatio, PwrSnsrCondCodeEnum * MarkerRatioCondCode);
	/**
	 * @brief Forthe specified marker, return the average power or voltage at the marker.
	 * The units are the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Marker Marker number.
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadMarkerAverage(SessionID Vi, const char * Channel, int Marker, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Forthe specified marker, return the maximum power or voltage at the marker. The units are the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Marker Marker number.
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadMarkerMax(SessionID Vi, const char * Channel, int Marker, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Forthe specified marker, return the minimum power or voltage at the marker. The units are the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Marker Marker number.
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadMarkerMin(SessionID Vi, const char * Channel, int Marker, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the average power or voltage in the time interval between marker 1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the minmum power or voltage in the time interval between marker 1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalFilteredMin(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the maximum filtered power or voltage in the time interval between marker 1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalFilteredMax(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the maximum instantaneous power or voltage in the time interval between marker1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalMax(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the minimum instantaneous power or voltage in the time interval between marker1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalMin(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the peak-to-average ratio of the power or voltage between marker 1 and marker 2. The units are dB for logarithmic channel units or percent for linear channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalPkToAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the average power or voltage in the time interval between marker 1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the minmum power or voltage in the time interval between marker 1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement. Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalFilteredMin(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the maximum filtered power or voltage in the time interval between marker 1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalFilteredMax(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the maximum instantaneous power or voltage in the time interval between marker1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalMax(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the minimum instantaneous power or voltage in the time interval between marker1 and marker 2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalMin(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the peak-to-average ratio of the power or voltage between marker 1 and marker 2. The units are dB for logarithmic channel units or percent for linear channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalPkToAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return maximum of the average power trace between MK1 and MK2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalMaxAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return minimum of the average power trace between MK1 and MK2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchIntervalMinAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return maximum of the average power trace between MK1 and MK2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalMaxAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return minimum of the average power trace between MK1 and MK2. The units will be the same as the specified channel.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadIntervalMinAvg(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the difference between MK1 and MK2. The units will be the same as marker units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMarkerDelta(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the ratio of MK1 to MK2. The units will be dB for logarithmic units or percent for linear units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMarkerRatio(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the difference between MK2 and MK1. The units will be the same as marker units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMarkerRDelta(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the ratio of MK2 to MK1. The units will be dB for logarithmic units or percent for linear units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMarkerRRatio(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);

	/**
	 * @brief Return the difference between MK1 and MK2. The units will be the same as marker units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadMarkerDelta(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the ratio of MK1 to MK2. The units will be dB for logarithmic units or percent for linear units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadMarkerRatio(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the difference between MK2 and MK1. The units will be the same as marker units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadMarkerRDelta(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/**
	 * @brief Return the ratio of MK2 to MK1. The units will be dB for logarithmic units or percent for linear units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.  Condition code.
	 * @param Val Measurement value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadMarkerRRatio(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, float* Val);
	/** @} */ // end of Marker

	/** @defgroup Display Display Functions
	*  Display functions
	*  @{
	*/
	/**
	* @brief Gets vertical center based on current units: arg = (range varies by units)
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param VerticalCenter Vertical center in units
	* @return Success (0) or error code.
	*/
	int EXPORT PwrSnsr_GetVerticalCenter(SessionID Vi, const char * Channel, float * VerticalCenter);
	/**
	* @brief Sets vertical center based on current units: arg = (range varies by units)
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param VerticalCenter Vertical center in units
	* @return Success (0) or error code.
	*/
	int EXPORT PwrSnsr_SetVerticalCenter(SessionID Vi, const char * Channel, float  VerticalCenter);
	/**
	* @brief Gets vertical scale based on current units: arg = (range varies by units)
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param VerticalScale Vertical scale in units
	* @return Success (0) or error code.
	*/
	int EXPORT PwrSnsr_GetVerticalScale(SessionID Vi, const char * Channel, float *  VerticalScale);
	/**
	* @brief Sets vertical scale based on current units: arg = (range varies by units)
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param VerticalScale Vertical scale in units
	* @return Success (0) or error code.
	*/
	int EXPORT PwrSnsr_SetVerticalScale(SessionID Vi, const char * Channel, float VerticalScale);
	/** @} */ // end of Display

	/** @defgroup StatisticalMode Statistical Mode
	*  Statmode functions
	*  @{
	*/
	/**
	 * @brief Get the statistical mode horizontal scale offset in dB.
	 * The offset value will appear at the leftmost edge of the scale with units dBr (decibels relative).
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param HorizontalOffset
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetHorizontalOffset(SessionID Vi, const char * Channel, double* HorizontalOffset);
	/**
	 * @brief Set the statistical mode horizontal scale offset in dB.
	 * The offset value will appear at the leftmost edge of the scale with units dBr (decibels relative).
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param HorizontalOffset
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetHorizontalOffset(SessionID Vi, const char * Channel, double HorizontalOffset);
	/**
	 * @brief Get the statistical mode horizontal scale in dB/Div.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param HorizontalScale
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetHorizontalScale(SessionID Vi, const char * Channel, double* HorizontalScale);
	/**
	 * @brief Set the statistical mode horizontal scale in dB/Div.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param HorizontalScale
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetHorizontalScale(SessionID Vi, const char * Channel, double HorizontalScale);
	

	/**
	 * @brief Returns the points in the CCDF trace.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TraceBufferSize
	 * @param Trace
	 * @param TraceActualSize
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchCCDFTrace(SessionID Vi, const char * Channel, int TraceBufferSize, float Trace[], int * TraceActualSize);
	/**
	 * @brief Resets statistical capturing mode by clearing the buffers and restarting the aquisition timer.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_StatModeReset(SessionID Vi, const char * Channel);
	/**
	 * @brief Returns an array of the current automatic statistical measurements performed
	 * on a sample population.
	 * @details Measurements performed are: long term average, peak
	 * and minimum amplitude, peak-to-average ratio, amplitude at the CCDF percent
	 * cursor, statistical percent at the CCDF power cursor, and the sample population
	 * size in samples. Note the peak-to-average ratio is returned in dB for logarithmic
	 * channel units, and percent for all other channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Pavg Long term average power in channel units.
	 * @param PavgCond Condition code.
	 * @param Ppeak Peak power in channel units.
	 * @param PpeakCond Condition code.
	 * @param Pmin Minimum power in channel units.
	 * @param PminCond Condition code.
	 * @param PkToAvgRatio Peak-to-average power in percent or dB.
	 * @param PkToAvgRatioCond Condition code.
	 * @param CursorPwr Power at the cursor in channel units.
	 * @param CursorPwrCond Condition code.
	 * @param CursorPct Statistical percent at the cursor.
	 * @param CursorPctCond Condition code.
	 * @param SampleCount Population size in samples.
	 * @param SampleCountCond Condition code.
	 * @param SecondsRun Number of seconds the measurement has run.
	 * @param SecondsRunCond Condition code.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchStatMeasurementArray(SessionID Vi, const char * Channel, double* Pavg, PwrSnsrCondCodeEnum * PavgCond, double* Ppeak,
		PwrSnsrCondCodeEnum * PpeakCond, double* Pmin, PwrSnsrCondCodeEnum * PminCond, double* PkToAvgRatio,
		PwrSnsrCondCodeEnum * PkToAvgRatioCond, double* CursorPwr, PwrSnsrCondCodeEnum * CursorPwrCond,
		double* CursorPct, PwrSnsrCondCodeEnum * CursorPctCond, double* SampleCount,
		PwrSnsrCondCodeEnum * SampleCountCond, double* SecondsRun, PwrSnsrCondCodeEnum * SecondsRunCond);

	/**
	 * @brief Return relative power (in dB) for a given percent on the CCDF plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Percent Statistical percent to retrieve power from.
	 * @param CondCode Condition code for the measurement.
	 * @param Val relative power at percent.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchCCDFPower(SessionID Vi, const char * Channel, double Percent, PwrSnsrCondCodeEnum * CondCode, double* Val);
	/**
	 * @brief Return relative power (in dB) for a given percent on the CCDF plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Power Relative power in dB
	 * @param CondCode Condition code for the measurement.
	 * @param Val Percent measurement at power.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchCCDFPercent(SessionID Vi, const char * Channel, double Power, PwrSnsrCondCodeEnum * CondCode, double* Val);
	/**
	 * @brief Get whether statistical capture is enabled.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Capture
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetCapture(SessionID Vi, const char * Channel, int* Capture);

	/**
	 * @brief Set whether statistical capture is enabled.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Capture
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetCapture(SessionID Vi, const char * Channel, int Capture);
	/**
	 * @brief Get whether statistical capture is enabled.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1". whether the statical capture is gated by markers or free-running.
	 * @param Gating
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetGating(SessionID Vi, const char * Channel, PwrSnsrStatGatingEnum * Gating);
	/**
	 * @brief Set whether the statical capture is gated by markers or free-running.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Gating
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetGating(SessionID Vi, const char * Channel, PwrSnsrStatGatingEnum Gating);
	/**
	 * @brief Get the termination action for statistical capturing.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TermAction
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTermAction(SessionID Vi, const char * Channel, PwrSnsrTermActionEnum * TermAction);
	/**
	 * @brief Set the termination action for statistical capturing.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TermAction
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTermAction(SessionID Vi, const char * Channel, PwrSnsrTermActionEnum TermAction);
	/**
	 * @brief Get the termination count for statistical capturing.
	 * After the sample count has been reached, the action determined by TermAction is taken.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TermCount
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTermCount(SessionID Vi, const char * Channel, double* TermCount);
	/**
	 * @brief Set the termination count for statistical capturing.
	 * After the sample count has been reached, the action determined by TermAction is taken.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TermCount
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTermCount(SessionID Vi, const char * Channel, double TermCount);
	/**
	 * @brief Get the termination time in seconds for statistical capturing.
	 * After the time has elapsed, the action determined by TermAction is taken.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TermTime
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTermTime(SessionID Vi, const char * Channel, int * TermTime);
	/**
	 * @brief Set the termination time in seconds (1 - 3600) for statistical capturing.
	 * After the time has elapsed, the action determined by TermAction is taken.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TermTime
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetTermTime(SessionID Vi, const char * Channel, int TermTime);
	/**
	 * @brief Get the number of points in the CCDF trace plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TraceCount
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetCCDFTraceCount(SessionID Vi, const char * Channel, int * TraceCount);
	/**
	 * @brief Set the number of points (1 - 16384) in the CCDF trace plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TraceCount
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetCCDFTraceCount(SessionID Vi, const char * Channel, int TraceCount);

	/**
	 * @brief Returns the percent CCDF at the cursor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchCursorPercent(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, double* Val);
	/**
	 * @brief Returns the power CCDF in dB at the cursor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchCursorPower(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum * CondCode, double* Val);
	/**
	 * @brief Get the cursor percent on the CCDF plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1". Channel Channel number. For single instruments, set this to 1.
	 * @param PercentPosition
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetPercentPosition(SessionID Vi, const char * Channel, double* PercentPosition);
	/**
	 * @brief Set the cursor percent on the CCDF plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PercentPosition
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetPercentPosition(SessionID Vi, const char * Channel, double PercentPosition);

	/**
	 * @brief Set the cursor power in dB on the CCDF plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PowerPosition
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetPowerPosition(SessionID Vi, const char * Channel, double PowerPosition);
	/**
	 * @brief Get the cursor power in dB on the CCDF plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PowerPosition
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetPowerPosition(SessionID Vi, const char * Channel, double* PowerPosition);

	/**
	 * @brief Returns data about the status of the acquisition system.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param SweepLength Returns the number of points in the trace.
	 * @param SampleRate Returns the sample rate.
	 * @param SweepRate Returns the number of triggered sweeps per second.
	 * @param SweepTime Returns the sweep time for the trace.
	 * @param StartTime Returns the start time relative to the trigger.
	 * @param StatusWord Internal use - acquisition system status word.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetAcqStatusArray(SessionID Vi, const char * Channel, int * SweepLength, double* SampleRate, double* SweepRate, double* SweepTime, double* StartTime, int * StatusWord);
	/**
	 * @brief Returns diagnostic data.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param DetectorTemp Temperature in degrees C at the RF detector.
	 * @param CpuTemp Temperature of the CPU in degrees C.
	 * @param MioVoltage Voltage at the Multi I/O port.
	 * @param VccInt10 Vcc 10 voltage.
	 * @param VccAux18 Vcc Aux 18 voltage.
	 * @param Vcc50 Vcc 50 voltage.
	 * @param Vcc25 Vcc 25 voltage.
	 * @param Vcc33 Vcc 33 voltage.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetDiagStatusArray(SessionID Vi, const char * Channel, float* DetectorTemp, float* CpuTemp, float* MioVoltage, float* VccInt10, float* VccAux18, float* Vcc50, float* Vcc25, float* Vcc33);
	/** @} */ // end of StatisticalMode


	




	/** @defgroup SensorInfo Sensor Info
	*  Sensor info functions
	*  @{
	*/
	/**
	 * @brief Date the sensor was manufactured in the following format YYYYmmDD.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ManufactureDateBufferSize Size of ManufactureDate in bytes.
	 * @param ManufactureDate Return value.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetManufactureDate(SessionID Vi, const char * Channel, int ManufactureDateBufferSize, char ManufactureDate[]);
	/**
	 * @brief Input impedance of the sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Impedance
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetImpedance(SessionID Vi, const char * Channel, float* Impedance);
	/**
	 * @brief Maximum power level the sensor can measure.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PeakPowerMax
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetPeakPowerMax(SessionID Vi, const char * Channel, float* PeakPowerMax);
	/**
	 * @brief Minimum power level the sensor can measure.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PeakPowerMin
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetPeakPowerMin(SessionID Vi, const char * Channel, float* PeakPowerMin);
	/**
	 * @brief Attenuation in dB for the sensor.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Attenuation
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetAttenuation(SessionID Vi, const char * Channel, float* Attenuation);
	/**
	 * @brief The date (YYYYmmDD) the last time the sensor was calibrated at the factory.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param FactoryCalDateBufferSize Size of FactoryCalDate in bytes.
	 * @param FactoryCalDate
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetFactoryCalDate(SessionID Vi, const char * Channel, int FactoryCalDateBufferSize, char FactoryCalDate[]);
	/**
	 * @brief Minimum internal trigger level in dBm.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param MinimumTrig
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMinimumTrig(SessionID Vi, const char * Channel, float* MinimumTrig);
	/**
	 * @brief Minimum frequency of RF the sensor can measure in high bandwidth.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param MinFreqHighBandwidth
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMinFreqHighBandwidth(SessionID Vi, const char * Channel, float* MinFreqHighBandwidth);
	/**
	 * @brief Maximum frequency carrier the sensor can measure in high bandwidth.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param MaxFreqHighBandwidth
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMaxFreqHighBandwidth(SessionID Vi, const char * Channel, float* MaxFreqHighBandwidth);
	/**
	 * @brief Minimum frequency carrier the sensor can measure in low bandwidth.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param MinFreqLowBandwidth
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMinFreqLowBandwidth(SessionID Vi, const char * Channel, float* MinFreqLowBandwidth);
	/**
	 * @brief Maximum frequency carrier the sensor can measure in low bandwidth.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param MaxFreqLowBandwidth
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMaxFreqLowBandwidth(SessionID Vi, const char * Channel, float* MaxFreqLowBandwidth);
	/**
	* @brief Get the sensor FPGA version.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param ValBufferSize Size pf Val in bytes
	* @param Val Buffer for staoring the version
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetFpgaVersion(SessionID Vi, const char * Channel, int ValBufferSize, char Val[]);

	/** @} */ // end of SensorInfo


	/** @defgroup UserCal User Calibration
	*  User calibration functions
	*  @{
	*/
	/**
	* @brief Instructs power meter to save the value of fixed cal, zero, and skew values.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @return Success (0) or error code.
	*/


	EXPORT int PwrSnsr_SaveUserCal(SessionID Vi, const char * Channel);
	/**
	* @brief Resets the value of fixed cal, zero, and skew to factory defaults.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_ClearUserCal(SessionID Vi, const char * Channel);

	/**
	 * @brief Gets the skew in seconds for the external trigger.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param External Trigger skew in seconds (-1e-6 to 1e-6).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetExternalSkew(SessionID Vi, const char * Channel, float* External);
	/**
	 * @brief Sets the skew in seconds for the external trigger.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param External Trigger skew in seconds (-1e-6 to 1e-6).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetExternalSkew(SessionID Vi, const char * Channel, float External);
	/**
	 * @brief Gets the skew in seconds for the slave trigger.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param SlaveSkew Trigger skew in seconds (-1e-6 to 1e-6).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetSlaveSkew(SessionID Vi, const char * Channel, float* SlaveSkew);
	/**
	 * @brief Sets the skew in seconds for the slave trigger.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param SlaveSkew Trigger skew in seconds (-1e-6 to 1e-6).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetSlaveSkew(SessionID Vi, const char * Channel, float SlaveSkew);
	/**
	 * @brief Gets the skew in seconds for the internal trigger.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param InternalSkew Trigger skew in seconds (-1e-6 to 1e-6).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetInternalSkew(SessionID Vi, const char * Channel, float* InternalSkew);
	/**
	 * @brief Sets the skew in seconds for the internal trigger.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param InternalSkew Trigger skew in seconds (-1e-6 to 1e-6).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetInternalSkew(SessionID Vi, const char * Channel, float InternalSkew);
	/**
	 * @brief Performs a zero offset null adjustment.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_Zero(SessionID Vi, const char * Channel);

	/**
	 * @brief Performs a zero offset null adjustment and returns true if successful.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Val Boolean value for operation success or failure.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ZeroQuery(SessionID Vi, const char * Channel, int* Val);
	/** @} */ // end of UserCal
	






	/** @defgroup Trace Trace Functions
	*  Trace functions
	*  @{
	*/

	/**
	 * @brief Get time spacing for each waveform point in seconds.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TimePerPoint Time spacing for each waveform point in seconds.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTimePerPoint(SessionID Vi, const char * Channel, float* TimePerPoint);
	/**
	 * @brief Get sweep time for the trace in seconds.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param SweepTime Sweep time for the trace in seconds.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetSweepTime(SessionID Vi, const char * Channel, float* SweepTime);
	/**
	 * @brief Get the number of points in the CCDF trace plot.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TraceCount The number of points in the CCDF trace plot.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetChanTraceCount(SessionID Vi, const char * Channel, int* TraceCount);
	/**
	 * @brief Get time offset (start time) of the trace in seconds. May be negative, indicating pre-trigger information.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param TraceStartTime Time offset (start time) of the trace in seconds. May be negative, indicating pre-trigger information.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTraceStartTime(SessionID Vi, const char * Channel, float* TraceStartTime);
	/**
	 * @brief Returns the actual detected power of the distal level in the current channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val Detected power of the distal level in the current channel units.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchDistal(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum* CondCode, float* Val);
	/**
	 * @brief Returns the actual detected power of the mesial level in the current channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val Detected power of the mesial level in the current channel units.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchMesial(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum* CondCode, float* Val);
	/**
	 * @brief Returns the actual detected power of the proximal level in the current channel units.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param CondCode Condition code for the measurement.
	 * @param Val Detected power of the proximal level in the current channel units.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchProximal(SessionID Vi, const char * Channel, PwrSnsrCondCodeEnum* CondCode, float* Val);

	/** @} */ // end of Trace


	/** @defgroup MultiplePulse Multiple Pulse
	*  MultiplePulse functions
	*  @{
	*/

	/**
	 * @brief Data structure containing pulse information.
	 *
	 */
	typedef struct PulseInfo
	{
		float Width; /**< Pulse width is defined as the interval between the first and second signal crossings of the mesial line. */
		float Peak; /**< Peak (max instanaeous) power measurement.  */
		float Min; /**< Minimum instanaeous power measurement. */
		float PulseAvg; /**< Average power measurement for the pulse.  */
		float Position; /**< Time position corresponding to the mesial crossing of the rising edge for the pulse. */
		float RiseProximal; /**<  Position in time for the proximal crossing on the rising edge of the pulse.*/
		float RiseDistal; /**< Position in time for the distal crossing on the rising edge of the pulse. */
		float RiseTime; /**< Rise time of the pulse. */
		float FallProximal; /**< Position in time for the proximal crossing on the falling edge of the pulse.*/
		float FallDistal; /**< Position in time for the distal crossing on the falling edge of the pulse. */
		float FallTime; /**< Fall time of the pulse. */
	}PulseInfo;
	/**
	 * @brief Return all previously acquired multiple pulse measurements.
	   The elements in the PulseInfos array correspond to pulses on the current trace from left to right (ascending time order).
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param PulseInfosSize Number of elements in PulseInfos array.
	 * @param PulseInfos Array to fill with multi pulse information.
	 * @param PulseInfosActualSize Actual number of valid elements in PulseInfos array.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_FetchAllMultiPulse(SessionID Vi,
		const char * Channel,
		int PulseInfosSize,
		PulseInfo PulseInfos[],
		int* PulseInfosActualSize);

	/** @} */ // end of MultiplePulse

	/** @defgroup MemChan Memory Channels
	*  Memory Channel functions
	*  @{
	*/
	/**
	 * @brief Saves the given channel to a memory channel. If the memory channel does not exist, a new one is created.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param MemChan Memory channel name. Must have the form MEM1...n, where n is the number of measurement channels. In single channel configurations, this parameter should always be "MEM1".
	 * @param ChannelName The channel name to copy from.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SaveToMemoryChannel(SessionID Vi, const char * MemChan, const char * ChannelName);
	/**
	 * @brief Returns an XML document containing settings and readings obtained using the SaveToMemoryChannel method.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param MemChan The name of the memory channel to get the archive from.
	 * @param ValBufferSize
	 * @param Val XML document containing settings and readings.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMemChanArchive(SessionID Vi, const char * MemChan, int ValBufferSize, char Val[]);
	/**
	 * @brief Loads the named memory channel using the given archive. If the memory channel does not exist, one is created.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param MemChan Memory channel name. Must have the form MEM1...n, where n is the number of measurement channels. In single channel configurations, this parameter should always be "MEM1".
	 * @param ArchiveContent An xml document containing settings and readings obtained using the SaveToMemoryChannel method. An archive can be obtained using the GetMemChanArchive method.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_LoadMemChanFromArchive(SessionID Vi, const char * MemChan, const char * ArchiveContent);
	 /** @} */ // end of MemChan



	
	/** @defgroup ModMeasStatus Modulated Measurements
	*  Modulated measurement functions
	*  @{
	*/
	/**
	 * @brief Returns true if modulated/CW measurement system is available. Will always return false if measurement buffer is enabled.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsAvailable True if modulated/CW measurement system is available. Will always return false if measurement buffer is enabled.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetIsAvailable(SessionID Vi, const char * Channel, int* IsAvailable);
	/**
	 * @brief Returns true if modulated/CW measuremnts are actively running.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param IsRunning True if modulated/CW measuremnts are actively running.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetIsRunning(SessionID Vi, const char * Channel, int* IsRunning);
	/**
	 * @brief Returns the period (rate) in seconds per new filtered reading.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ReadingPeriod The period (rate) in seconds per new filtered reading.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetReadingPeriod(SessionID Vi, const char * Channel, float* ReadingPeriod);
	/** @} */



	/** @defgroup MeasurementBuffer Measurement Buffer
	*  Measurement Buffer functions
	*  @{
	*/

	/**
	 * @brief Get the average power measurements that were captured during the last call to AcquireMeasurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Buffer size of Val.
	 * @param Val Array of average measurements.
	 * @param ValActualSize Actual size of Val.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetBufferedAverageMeasurements(SessionID Vi, const char * Channel, int ValBufferSize,
		float Val[], int* ValActualSize);
	/**
	 * @brief Initiates new acquisition from the measurement buffer system (if acquisition is in the stopped state).
	 * Blocks until the number of measurements for each enabled channel is equal to count, or a time out has occurred.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Timeout Maximum time in seconds to continue acquiring samples. Negative values will be treated as infinite.
	 * @param Count Number of samples to acquire.
	 * @param StopReason Reason aqcuisition stopped.
	 * @param Val Number of samples acquired.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_AcquireMeasurements(SessionID Vi, double Timeout, int Count, PwrSnsrMeasBuffStopReasonEnum* StopReason, int* Val);
	/**
	 * @brief Get the maximum power measurements that were captured during the last call to AcquireMeasurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of max measurements.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMaxMeasurements(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Get the minimum power measurements that were captured during the last call to AcquireMeasurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of min measurements.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMinMeasurements(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Get the time duration samples are captured during each timed mode acquisiton.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Duration The duration in seconds samples are captured during each timed mode acquisiton.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetDuration(SessionID Vi, float* Duration);
	/**
	 * @brief Set the duration samples are captured during each timed mode acquisition.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Duration The duration samples are captured during each timed mode acquisition in seconds.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetDuration(SessionID Vi, float Duration);
	/**
	 * @brief Get the sequence number entries that were captured during the last call to AcquireMeasurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of sequence numbers.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetSequenceNumbers(SessionID Vi, const char * Channel, int ValBufferSize, unsigned int Val[],
		int* ValActualSize);
	/**
	 * @brief Get the start time entries in seconds that were captured during the last call to AcquireMeasurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of start times.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetStartTimes(SessionID Vi, const char * Channel, int ValBufferSize, double Val[],
		int* ValActualSize);
	/**
	 * @brief Get the duration entries in seconds that were captured during the last call to AcquireMeasurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of measurement durations in seconds.
	 * @param ValActualSize Actual size of the returned buffer.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetDurations(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Starts measurement buffer acquisition. This method allows the user to send a command to the power meter to begin buffering measurements without waiting for all measurements to be completed.
	 * Alternately, you can call the AcquireReadings method to start buffering measurements and wait for them to be read from the meter.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_StartAcquisition(SessionID Vi);
	/**
	 * @brief Sends a command to stop the measurement buffer from acquiring readings.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_StopAcquisition(SessionID Vi);
	/**
	 * @brief Sends a command to the power meter to clear all buffered readings. This method does not clear cached measurements accessible through GetAverageMeasurements, etc.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ClearBuffer(SessionID Vi);
	/**
	 * @brief Clears cached average, min, max, duration, start time, and sequence number measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ClearMeasurements(SessionID Vi);
	/**
	 * @brief Get the number of measurement entries available that were captured during AcquireMeasurements().
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Val Number of measurement entries available.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMeasurementsAvailable(SessionID Vi, const char * Channel, int* Val);
	/**
	 * @brief Set the period each timed mode acquisition (measurement buffer) is started.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Period The period in seconds each timed mode acquisition is started.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetPeriod(SessionID Vi, float Period);
	/**
	 * @brief Get the period each timed mode acquisition (measurement buffer) is started.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Period The period in seconds each timed mode acquisition is started.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetPeriod(SessionID Vi, float* Period);
	/**
	* @brief Get the flag indicating which measurement buffer arrays will be read when calling PwrSnsr_AcquireMeasurements.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param Flag Bit masked value indicating which measurement arrays will be queried (see PwrSnsrRdgsEnableFlag).
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetRdgsEnableFlag(SessionID Vi, int* Flag);
	/**
	 * @brief Set the flag indicating which measurement buffer arrays will be read when calling PwrSnsr_AcquireMeasurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Flag Bit masked value indicating which measurement arrays will be queried (see PwrSnsrRdgsEnableFlag).
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetRdgsEnableFlag(SessionID Vi, int Flag);
	/**
	 * @brief Each Measurement Buffer Entry is controlled by a buffer gate that defines the start and end of the entry time interval.
	 * The gate signal may be internally or externally generated in several different ways.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param GateMode Buffer gate mode that defines the start and end of the entry time interval.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetGateMode(SessionID Vi, PwrSnsrMeasBuffGateEnum * GateMode);
	/**
	 * @brief  Each Measurement Buffer Entry is controlled by a buffer gate that defines the start and end of the entry time interval.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param GateMode Buffer gate mode that defines the start and end of the entry time interval.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetGateMode(SessionID Vi, PwrSnsrMeasBuffGateEnum GateMode);
	/**
	 * @brief Get the mode used to start acquisition of buffer entries.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param StartMode Mode used to start acquisition of buffer entries.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetStartMode(SessionID Vi, PwrSnsrMeasBuffStartModeEnum * StartMode);
	/**
	 * @brief Set the mode used to start acquisition of buffer entries.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param StartMode Mode used to start acquisition of buffer entries.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetStartMode(SessionID Vi, PwrSnsrMeasBuffStartModeEnum StartMode);
	/**
	 * @brief Send a command to the meter to notify it the user is done reading and to advance the read index.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_AdvanceReadIndex(SessionID Vi);
	/**
	 * @brief Query the power meter for all buffered average power measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer in elements.
	 * @param Val Array of average power measurements.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_QueryAverageMeasurements(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Query the power meter for all buffered start times in seconds.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of start times in seconds.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_QueryStartTimes(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Query the power meter for all buffered sequence numbers.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of sequence numbers.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_QuerySequenceNumbers(SessionID Vi, const char * Channel, int ValBufferSize, unsigned int Val[],
		int* ValActualSize);
	/**
	 * @brief Query the power meter for all buffered measurement durations in seconds.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of buffered measurement durations.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_QueryDurations(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Query the power meter for all buffered maximum power measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of max measurements.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_QueryMaxMeasurements(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Query the power meter for all buffered minimum power measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Array of min measurements.
	 * @param ValActualSize Actual size of the returned array in elements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_QueryMinMeasurements(SessionID Vi, const char * Channel, int ValBufferSize, float Val[],
		int* ValActualSize);
	/**
	 * @brief Get whether the measurement buffer is set to overwrite members that have not been read by the user.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param WriteProtection Returns trueif the measurement buffer is allowed to overwrite members that have not been read by the user.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetWriteProtection(SessionID Vi, int* WriteProtection);
	/**
	 * @brief Check if the last measurement buffer session timed out.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param TimedOut True if the last measurement buffer session timed out.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetTimedOut(SessionID Vi, int* TimedOut);
	/**
	 * @brief Get the count of elements for this measurement buffer session. Set to 0 for the meter to continuously acquire measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param SessionCount Get the count of elements for this measurement buffer session. Set to 0 for the meter to continuously acquire measurements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetSessionCount(SessionID Vi, int* SessionCount);
	/**
	 * @brief Set the count of elements for this measurement buffer session. Set to 0 for the meter to continuously acquire measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param SessionCount Set the count of elements for this measurement buffer session. Set to 0 for the meter to continuously acquire measurements.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetSessionCount(SessionID Vi, int SessionCount);
	/**
	 * @brief Set the count of elements for this measurement buffer session. Set to 0 for the meter to continuously acquire measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Seconds Set the time out value. Values less than or equal to 0 will be treated as infinite. Valid range : 0.001 to 1000
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetSessionTimeout(SessionID Vi, float Seconds);

	/**
	 * @brief Get the return count for each measurement query.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param ReturnCount The return count for each measurement query.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetReturnCount(SessionID Vi, int* ReturnCount);
	/**
	 * @brief Set the return count for each measurement query.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param ReturnCount The return count for each measurement query.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetReturnCount(SessionID Vi, int ReturnCount);
	/**
	 * @brief Set whether to allow the measurement buffer to overwrite entries that have not been read by the user.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param WriteProtection Set false to allow the measurement buffer to overwrite entries that have not been read by the user.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetWriteProtection(SessionID Vi, int WriteProtection);
	/**
	 * @brief Get flag indicating whether the power meter's internal buffer filled up before being emptied.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param OverRan True if the power meter's internal buffer filled up before being emptied.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetOverRan(SessionID Vi, int* OverRan);
	/**
	 * @brief Gets the number of measurements available in the power meter's internal buffer. Note: The number of readings that have been acquired may be more or less.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param MeasurementsAvailable The number of measurements available in the power meter's internal buffer. Note: The number of readings that have been acquired may be more or less.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetBufferedMeasurementsAvailable(SessionID Vi, int* MeasurementsAvailable);
	/**
	 * @brief Get whether the measurement buffer has been enabled.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param MeasBuffEnabled True if measurement buffer is enabled.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetMeasBuffEnabled(SessionID Vi, int* MeasBuffEnabled);
	/**
	 * @brief Enable or disable the measurement buffer. Disabling the measurement buffer enables modulated/CW measurements. Conversely, enabling it disables modulated/CW measurements.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param MeasBuffEnabled True to enable measurement buffer, false to disable.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetMeasBuffEnabled(SessionID Vi, int MeasBuffEnabled);
	/**
	 * @brief Sets a flag indicating to restart continuous capture. This method allows the user to restart continuous acquisition. Has no effect if ContinuousCapture is set to false.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ResetContinuousCapture(SessionID Vi);



	/**
	 * @brief Get delay time added to the detected end of a burst for analysis. Typically negative. Typically used to exclude the falling edge of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param EndDelay The delay time added to the detected end of a burst for analysis.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetEndDelay(SessionID Vi, float* EndDelay);
	/**
	 * @brief Set delay time added to the detected end of a burst for analysis. Typically negative. Typically used to exclude the falling edge of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param EndDelay Delay time added to the detected end of a burst for analysis.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetEndDelay(SessionID Vi, float EndDelay);
	/**
	 * @brief Get the minimum amount of time power remains above the trigger point to be counted as the beginning of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param StartQual The minimum amount of time power remains above the trigger point to be counted as the beginning of a burst.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetStartQual(SessionID Vi, float* StartQual);
	/**
	 * @brief Set the minimum amount of time power remains above the trigger point to be counted as the beginning of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param StartQual The minimum amount of time power remains above the trigger point to be counted as the beginning of a burst.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetStartQual(SessionID Vi, float StartQual);
	/**
	 * @brief Get delay time added to the detected beginning of a burst for analysis. Typically used to exclude the rising edge of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param StartDelay Delay time in seconds added to the detected beginning of a burst for analysis.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetStartDelay(SessionID Vi, float* StartDelay);
	/**
	 * @brief Set delay time added to the detected beginning of a burst for analysis. Typically used to exclude the rising edge of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param StartDelay Delay time in seconds added to the detected beginning of a burst for analysis.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetStartDelay(SessionID Vi, float StartDelay);
	/**
	 * @brief Get the minimum amount of time power remains below the trigger point to be counted as the end of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param EndQual The minimum amount of time power remains below the trigger point to be counted as the end of a burst.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_GetEndQual(SessionID Vi, float* EndQual);
	/**
	 * @brief Set the minimum amount of time power remains below the trigger point to be counted as the end of a burst.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param EndQual The minimum amount of time power remains below the trigger point to be counted as the end of a burst.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_SetEndQual(SessionID Vi, float EndQual);
	/**
	* @brief Set whether AcquireMeasurements will stop the measurement buffer session or continue capturing measurement buffer entries after being called.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param ContinuousCapture True to set whether AcquireMeasurements will stop the measurement buffer session or continue capturing measurement buffer entries after being called.
	* @return Success (0) or error code.
	*/

	EXPORT int PwrSnsr_SetContinuousCapture(SessionID Vi, int ContinuousCapture);
	/**
	* @brief Get whether AcquireMeasurements will stop the measurement buffer session or continue capturing measurement buffer entries after being called.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	* @param ContinuousCapture True if AcquireMeasurements will stop the measurement buffer session or continue capturing measurement buffer entries after being called.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetContinuousCapture(SessionID Vi, int* ContinuousCapture);
	/** @} */ // End of MeasurementBuffer
	
	/** @defgroup RawIO Sensor RawIO 
	*  Sensor RawIO functions
	*  @{
	*/
	/**
	 * @brief Write a byte array to the meter.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param DataBufferSize Size of the buffer in bytes.
	 * @param Data Data to send.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_Write(SessionID Vi, const char * Channel, int DataBufferSize, unsigned char Data[]);
	/**
	 * @brief Reads byte array from the meter.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Count Maximum count of bytes to return.
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Byte array from the USB.
	 * @param ValActualSize Actual size of the returned array in bytes.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadByteArray(SessionID Vi, const char * Channel, int Count, int ValBufferSize, unsigned char Val[],
		int* ValActualSize);
	/**
	 * @brief Reads a control transfer on the USB.
	 * @param Vi The SessionID handle that you obtain from the PwrSnsr_init function. The handle identifies a particular instrument session.
	 * @param Channel Channel number. For single instruments, set this to "CH1".
	 * @param Count Maximum count to return.
	 * @param ValBufferSize Size of the buffer.
	 * @param Val Byte array from a USB control transfer.
	 * @param ValActualSize Actual size of the returned array in bytes.
	 * @return Success (0) or error code.
	 */
	EXPORT int PwrSnsr_ReadControl(SessionID Vi, const char * Channel, int Count, int ValBufferSize, unsigned char Val[],
		int* ValActualSize);
	/** @} */ // end of RawIO


	
	/** @defgroup License License Functions
	*  License functions (Windows Only)
	*  @{
	*/

	/**
	* @brief Get the hardware license serial number.
	* @param val Serial number of the license dongle
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetDongleSerialNumber(long* val);
	/**
	* @brief Get the hardware license expiration date.
	* @param Date expiration date in the format YYYYMMDD
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetExpirationDate(int* Date);
	/**
	* @brief Get the number of calibrations left on the license.
	* @param val Number of cals left.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetNumberOfCals(long * val);
	/**
	* @brief Get whether the hardware license dongle is connected.
	* @param val Boolean. 1 for connected or 0 for not connected.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_IsLicenseDongleConnected(int * val);
	/** @} */ // end of License

	/** @defgroup SensorSimulation Sensor Simulation
	*  Sensor simulation functions
	*  @{
	*/

	/**
	* Unit selector for watts or dBm.
	*/
	typedef enum PwrSnsrSignalUnits
	{
		PwrSnsrSignalUnitsdBm = 0, /**< dBm.*/
		PwrSnsrSignalUnitsWatts = 1, /**< Watts.*/

	} PwrSnsrSignalUnits;

	/**
	* Simulated signal type.
	*/
	typedef enum PwrSnsrSimSignalType
	{
		PwrSnsrSimSignalPeriodic = 0, /**< Periodic waveform defined by PRF and duty cycle.*/
		PwrSnsrSimSignalBurst = 1, /**< IFF-like burst signal.*/

	} PwrSnsrSimSignalType;

	/**
	* Simulated signal parameter setting weight.
	*/
	typedef enum PwrSnsrSimParamWeight
	{
		PwrSnsrWeightNone = 0, /**< Setting is off.*/
		PwrSnsrWeightLight = 1, /**< Setting is lightly applied.*/
		PwrSnsrWeightMedium = 2, /**< Setting is moderately applied.*/
		PwrSnsrWeightHeavy = 3, /**< Setting is heavily applied.*/

	} PwrSnsrSimParamWeight;

	/**
	* @brief Open a simulated power meter session
	* @param NumChans Number of channels
	* @param ResourceBuff Buffer to read back the session name, can be NULL
	* @param ResourceBuffSize size of ResourceBuff in characters
	* @param Vi SessionID handle (out parameter)
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_OpenSimMeter(int NumChans, char * ResourceBuff, int ResourceBuffSize, SessionID * Vi);

	/**
	* @brief Set the amplitude for the signal on a simulation channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Amplitude The simulated signal level
	* @param Units Units of amplitude in dBm or Watts
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetSimSignalAmplitude(SessionID Vi, const char * Channel, float Amplitude, PwrSnsrSignalUnits Units);

	/**
	* @brief Get the amplitude for the signal on a simulation channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Amplitude The simulated signal level (return value).
	* @param Units Units of amplitude in dBm or Watts
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetSimSignalAmplitude(SessionID Vi, const char * Channel, float * Amplitude, PwrSnsrSignalUnits Units);

	/**
	* @brief Set the percent modulation for the signal on a simulation channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Weight The relative modulation setting.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetSimSignalModulation(SessionID Vi, const char * Channel, PwrSnsrSimParamWeight Weight);

	/**
	* @brief Get the percent modulation for the signal on a simulation channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Weight The relative modulation setting (return value).	
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetSimSignalModulation(SessionID Vi, const char * Channel, PwrSnsrSimParamWeight * Weight);

	/**
	* @brief Set the percent compression for the signal on a simulation channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Weight The relative compression setting.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetSimSignalCompression(SessionID Vi, const char * Channel, PwrSnsrSimParamWeight Weight);

	/**
	* @brief Get the percent compression for the signal on a simulation channel.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Weight The relative compression setting (return value).	
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetSimSignalCompression(SessionID Vi, const char * Channel, PwrSnsrSimParamWeight * Weight);

	/**
	* @brief Set the simulated channel signal type.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param SignalType The simulated signal type.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetSimSignalType(SessionID Vi, const char * Channel, PwrSnsrSimSignalType SignalType);

	/**
	* @brief Get the simulated channel signal type.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param SignalType The simulated signal type (return value).
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetSimSignalType(SessionID Vi, const char * Channel, PwrSnsrSimSignalType * SignalType);

	/**
	* @brief Set the simulated signal PRF. Valid for Periodic and Burst.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param PRF Pulse repetition frequency in Hz.
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetSimSignalPRF(SessionID Vi, const char * Channel, float PRF);

	/**
	* @brief Get the simulated signal PRF. Valid for Periodic and Burst.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param PRF Pulse repetition frequency in Hz (return value).
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetSimSignalPRF(SessionID Vi, const char * Channel, float * PRF);

	/**
	* @brief Set the simulated signal duty cycle in percent. Affects Periodic only.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Duty Duty cycle in percent ( < 99.0).
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_SetSimSignalDuty(SessionID Vi, const char * Channel, float Duty);

	/**
	* @brief Get the simulated signal duty cycle in percent. Affects Periodic only.
	* @param Vi The SessionID handle that you obtain from the PwrSnsr_OpenSimMeter function. The handle identifies a particular instrument session.
	* @param Channel Channel number. For single instruments, set this to "CH1".
	* @param Duty Duty cycle in percent (return value).
	* @return Success (0) or error code.
	*/
	EXPORT int PwrSnsr_GetSimSignalDuty(SessionID Vi, const char * Channel, float * Duty);

	/** @} */ // end of SensorSimulation



#ifdef __cplusplus
}
#endif

#endif /* PWRSNSRLIB_H */
