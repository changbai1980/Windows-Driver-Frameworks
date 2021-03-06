/*++

Copyright (c) Microsoft Corporation

Module Name:

    FxPnpCallbacks.hpp

Abstract:

    This module implements the PnP/Power callback objects.

Author:



Environment:

    Both kernel and user mode

Revision History:

--*/

#ifndef _FXPNPCALLBACKS_H_
#define _FXPNPCALLBACKS_H_

#include "FxPkgPnp.hpp"
#include "FxCxPnpPowerCallbacks.hpp"
#include "DbgTrace.h"



class FxPnpDeviceFilterResourceRequirements : public FxCallback {

public:
    PFN_WDF_DEVICE_FILTER_RESOURCE_REQUIREMENTS m_Method;

    FxPnpDeviceFilterResourceRequirements(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE Device,
        __in WDFIORESREQLIST Collection
        );
};

class FxPnpDeviceD0Entry : public FxPrePostCallback {

public:
    FxPnpDeviceD0Entry(
        VOID
        ) : m_Method(NULL)
    {
    }

    __drv_when(!NT_SUCCESS(return), __drv_arg(Progress, _Must_inspect_result_))
    _Must_inspect_result_
    NTSTATUS
    Invoke(
        _In_ WDFDEVICE  Device,
        _In_ WDF_POWER_DEVICE_STATE PreviousState,
        _Out_ FxCxCallbackProgress *Progress
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_D0_ENTRY Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );

    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

    VOID
    InvokeCxCleanupCallback(
        _In_ PFxCxPnpPowerCallbackContext Context
        );

#if (FX_CORE_MODE == FX_CORE_KERNEL_MODE)
    NTSTATUS
    InvokeCompanionCallback(
        _In_ FxCompanionTarget* CompanionTarget
        );
#endif

private:
    PFN_WDF_DEVICE_D0_ENTRY m_Method;
    WDFDEVICE               m_Device;
    WDF_POWER_DEVICE_STATE  m_PreviousState;   
};

class FxPnpDeviceD0EntryPostInterruptsEnabled : public FxCallback {

public:
    PFN_WDF_DEVICE_D0_ENTRY_POST_INTERRUPTS_ENABLED m_Method;

    FxPnpDeviceD0EntryPostInterruptsEnabled(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE  Device,
        __in WDF_POWER_DEVICE_STATE PreviousState
        );
};

class FxPnpDeviceD0Exit : public FxPrePostCallback {

public:
    FxPnpDeviceD0Exit(
        VOID
        ) : m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        _In_ WDFDEVICE  Device,
        _In_ WDF_POWER_DEVICE_STATE TargetState
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_D0_EXIT Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );

    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );
#if (FX_CORE_MODE == FX_CORE_KERNEL_MODE)
    NTSTATUS
    InvokeCompanionCallback(
        _In_ FxCompanionTarget* CompanionTarget
        );
#endif
private:
    PFN_WDF_DEVICE_D0_EXIT  m_Method;
    WDFDEVICE               m_Device;
    WDF_POWER_DEVICE_STATE  m_TargetState;
};

class FxPnpDeviceD0ExitPreInterruptsDisabled : public FxCallback {

public:
    PFN_WDF_DEVICE_D0_EXIT_PRE_INTERRUPTS_DISABLED m_Method;

    FxPnpDeviceD0ExitPreInterruptsDisabled(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE  Device,
        __in WDF_POWER_DEVICE_STATE TargetState
        );
};

class FxPnpDevicePrepareHardware : public FxPrePostCallback {

public:
    FxPnpDevicePrepareHardware(
        VOID
        ) : m_Method(NULL)
    {
    }

    __drv_when(!NT_SUCCESS(return), __drv_arg(Progress, _Must_inspect_result_))
    _Must_inspect_result_
    NTSTATUS
    Invoke(
        _In_ WDFDEVICE  Device,
        _In_ WDFCMRESLIST ResourcesRaw,
        _In_ WDFCMRESLIST ResourcesTranslated,
        _Out_ FxCxCallbackProgress *Progress
        );
    
    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_PREPARE_HARDWARE Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );

    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

    VOID
    InvokeCxCleanupCallback(
        _In_ PFxCxPnpPowerCallbackContext Context
        );

#if (FX_CORE_MODE == FX_CORE_KERNEL_MODE)
    NTSTATUS
    InvokeCompanionCallback(
        _In_ FxCompanionTarget* CompanionTarget
        );
#endif
private:
    PFN_WDF_DEVICE_PREPARE_HARDWARE m_Method;
    WDFDEVICE                       m_Device;
    WDFCMRESLIST                    m_ResourcesRaw;
    WDFCMRESLIST                    m_ResourcesTranslated;
    
};

class FxPnpDeviceReleaseHardware : public FxPrePostCallback {

public:
    FxPnpDeviceReleaseHardware(
        VOID
        ) : m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE  Device,
        __in WDFCMRESLIST ResourcesTranslated
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_RELEASE_HARDWARE Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );
    
    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

#if (FX_CORE_MODE == FX_CORE_KERNEL_MODE)
    NTSTATUS
    InvokeCompanionCallback(
        _In_ FxCompanionTarget* CompanionTarget
        );
#endif
private:
    PFN_WDF_DEVICE_RELEASE_HARDWARE m_Method;
    WDFDEVICE                       m_Device;
    WDFCMRESLIST                    m_ResourcesTranslated;
    
};

class FxPnpDeviceRemoveAddedResources : public FxCallback {

public:
    PFN_WDF_DEVICE_REMOVE_ADDED_RESOURCES m_Method;

    FxPnpDeviceRemoveAddedResources(
        VOID
        )  : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE Device,
        __in WDFCMRESLIST ResourcesRaw,
        __in WDFCMRESLIST ResourcesTranslated
        );
};

class FxPnpDeviceSelfManagedIoCleanup : public FxPrePostCallback {

public:
    FxPnpDeviceSelfManagedIoCleanup(
        VOID
        ) : m_Method(NULL)
    {
    }

    VOID
    Invoke(
        _In_  WDFDEVICE  Device
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_SELF_MANAGED_IO_CLEANUP Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );
    
    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

private:
    PFN_WDF_DEVICE_SELF_MANAGED_IO_CLEANUP m_Method;
    WDFDEVICE                              m_Device;
    
};

class FxPnpDeviceSelfManagedIoFlush : public FxPrePostCallback {

public:
    FxPnpDeviceSelfManagedIoFlush(
        VOID
        ) : m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in  WDFDEVICE  Device
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_SELF_MANAGED_IO_FLUSH Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );
    
    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

private:
    PFN_WDF_DEVICE_SELF_MANAGED_IO_FLUSH m_Method;
    WDFDEVICE                            m_Device;
    
};

class FxPnpDeviceSelfManagedIoInit : public FxPrePostCallback {

public:
    FxPnpDeviceSelfManagedIoInit(
        VOID
        ) : m_Method(NULL)
    {
    }

    __drv_when(!NT_SUCCESS(return), __drv_arg(Progress, _Must_inspect_result_))
    _Must_inspect_result_
    NTSTATUS
    Invoke(
        _In_  WDFDEVICE  Device,
        _Out_ FxCxCallbackProgress *Progress
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_SELF_MANAGED_IO_INIT Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );
    
    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

    VOID
    InvokeCxCleanupCallback(
        _In_ PFxCxPnpPowerCallbackContext Context
        );

private:
    PFN_WDF_DEVICE_SELF_MANAGED_IO_INIT m_Method;
    WDFDEVICE  m_Device;
};

class FxPnpDeviceSelfManagedIoSuspend : public FxPrePostCallback {

public:
    FxPnpDeviceSelfManagedIoSuspend(
        VOID
        ) : m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        _In_  WDFDEVICE  Device
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_SELF_MANAGED_IO_SUSPEND Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );
        
    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

private:
    PFN_WDF_DEVICE_SELF_MANAGED_IO_SUSPEND m_Method;
    WDFDEVICE  m_Device;
};

class FxPnpDeviceSelfManagedIoRestart : public FxPrePostCallback {

public:
    FxPnpDeviceSelfManagedIoRestart(
        VOID
        ) : m_Method(NULL)
    {
    }

    __drv_when(!NT_SUCCESS(return), __drv_arg(Progress, _Must_inspect_result_))
    _Must_inspect_result_
    NTSTATUS
    Invoke(
        _In_  WDFDEVICE  Device,
        _Out_ FxCxCallbackProgress *Progress
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_SELF_MANAGED_IO_RESTART Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );
    
    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

    VOID
    InvokeCxCleanupCallback(
        _In_ PFxCxPnpPowerCallbackContext Context
        );

private:
    PFN_WDF_DEVICE_SELF_MANAGED_IO_RESTART m_Method;

    WDFDEVICE m_Device;
};

class FxPnpDeviceQueryStop : public FxCallback {

public:
    PFN_WDF_DEVICE_QUERY_STOP m_Method;

    FxPnpDeviceQueryStop(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in  WDFDEVICE  Device
        );
};

class FxPnpDeviceQueryRemove : public FxCallback {

public:
    PFN_WDF_DEVICE_QUERY_REMOVE m_Method;

    FxPnpDeviceQueryRemove(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in  WDFDEVICE  Device
        );
};

class FxPnpDeviceResourcesQuery : public FxCallback {

public:
    PFN_WDF_DEVICE_RESOURCES_QUERY m_Method;

    FxPnpDeviceResourcesQuery(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE  Device,
        __in WDFCMRESLIST Collection
        );
};

class FxPnpDeviceResourceRequirementsQuery : public FxCallback {

public:
    PFN_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY m_Method;

    FxPnpDeviceResourceRequirementsQuery(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE  Device,
        __in WDFIORESREQLIST Collection
        );
};

class FxPnpDeviceEject : public FxCallback {

public:
    PFN_WDF_DEVICE_EJECT m_Method;

    FxPnpDeviceEject(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE  Device
        );
};

class FxPnpDeviceSurpriseRemoval : public FxPrePostCallback {

public:
    FxPnpDeviceSurpriseRemoval(
        VOID
        ) : m_Method(NULL)
    {
    }

    VOID
    Invoke(
        _In_ WDFDEVICE  Device
        );

    VOID
    Initialize(
        _In_ FxPkgPnp* PkgPnp,
        _In_ PFN_WDF_DEVICE_SURPRISE_REMOVAL Method
        );

protected:
    _Must_inspect_result_
    NTSTATUS
    InvokeClient(
        VOID
        );
    
    _Must_inspect_result_
    NTSTATUS
    InvokeCxCallback(
        _In_ PFxCxPnpPowerCallbackContext Context,
        _In_ FxCxInvokeCallbackSubType PrePost
        );

private:
    PFN_WDF_DEVICE_SURPRISE_REMOVAL m_Method;
    WDFDEVICE                       m_Device;
};

class FxPnpDeviceUsageNotification : public FxCallback {

public:
    PFN_WDF_DEVICE_USAGE_NOTIFICATION m_Method;

    FxPnpDeviceUsageNotification(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device,
        __in WDF_SPECIAL_FILE_TYPE NotificationType,
        __in BOOLEAN InPath
        );
};

class FxPnpDeviceUsageNotificationEx : public FxCallback {

public:
    PFN_WDF_DEVICE_USAGE_NOTIFICATION_EX m_Method;

    FxPnpDeviceUsageNotificationEx(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE Device,
        __in WDF_SPECIAL_FILE_TYPE NotificationType,
        __in BOOLEAN InPath
        );
};

class FxPnpDeviceRelationsQuery : public FxCallback {

public:
    PFN_WDF_DEVICE_RELATIONS_QUERY m_Method;

    FxPnpDeviceRelationsQuery(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device,
        __in DEVICE_RELATION_TYPE RelationType
        );
};

class FxPnpDeviceSetLock : public FxCallback {

public:
    PFN_WDF_DEVICE_SET_LOCK m_Method;

    FxPnpDeviceSetLock(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE Device,
        __in BOOLEAN Lock
        );
};

class FxPnpDeviceReportedMissing : public FxCallback {

public:
    PFN_WDF_DEVICE_REPORTED_MISSING m_Method;

    FxPnpDeviceReportedMissing(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device
        );
};

class FxPowerDeviceEnableWakeAtBus :  public FxCallback {

public:
    PFN_WDF_DEVICE_ENABLE_WAKE_AT_BUS m_Method;

    FxPowerDeviceEnableWakeAtBus(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE Device,
        __in SYSTEM_POWER_STATE PowerState
        );
};

class FxPowerDeviceDisableWakeAtBus :  public FxCallback {

public:
    PFN_WDF_DEVICE_DISABLE_WAKE_AT_BUS m_Method;

    FxPowerDeviceDisableWakeAtBus(
        VOID
        ) : FxCallback(), m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device
        );
};

class FxPowerDeviceArmWakeFromS0 :  public FxCallback {

public:
    PFN_WDF_DEVICE_ARM_WAKE_FROM_S0 m_Method;

    FxPowerDeviceArmWakeFromS0(
        VOID
        ) : m_Method(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE Device
        );
};

class FxPowerDeviceArmWakeFromSx :  public FxCallback {

public:
    PFN_WDF_DEVICE_ARM_WAKE_FROM_SX m_Method;
    PFN_WDF_DEVICE_ARM_WAKE_FROM_SX_WITH_REASON m_MethodWithReason;

    FxPowerDeviceArmWakeFromSx(
        VOID
        ) : m_Method(NULL),
            m_MethodWithReason(NULL)
    {
    }

    _Must_inspect_result_
    NTSTATUS
    Invoke(
        __in WDFDEVICE Device,
        __in BOOLEAN DeviceWakeEnabled,
        __in BOOLEAN ChildrenArmedForWake
        );
};

class FxPowerDeviceDisarmWakeFromS0 :  public FxCallback {

public:
    PFN_WDF_DEVICE_DISARM_WAKE_FROM_S0 m_Method;

    FxPowerDeviceDisarmWakeFromS0(
        VOID
        ) : m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device
        );
};

class FxPowerDeviceDisarmWakeFromSx :  public FxCallback {

public:
    PFN_WDF_DEVICE_DISARM_WAKE_FROM_SX m_Method;

    FxPowerDeviceDisarmWakeFromSx(
        VOID
        ) : m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device
        );
};

class FxPowerDeviceWakeFromSxTriggered :  public FxCallback {

public:
    PFN_WDF_DEVICE_WAKE_FROM_SX_TRIGGERED m_Method;

    FxPowerDeviceWakeFromSxTriggered(
        VOID
        ) : m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device
        );
};

class FxPowerDeviceWakeFromS0Triggered :  public FxCallback {

public:
    PFN_WDF_DEVICE_WAKE_FROM_S0_TRIGGERED m_Method;

    FxPowerDeviceWakeFromS0Triggered(
        VOID
        ) : m_Method(NULL)
    {
    }

    VOID
    Invoke(
        __in WDFDEVICE Device
        );
};

struct FxPnpStateCallbackInfo {
    //
    // Bit field of WDF_STATE_NOTIFICATION_TYPE defined values
    //
    ULONG Types;

    //
    // Function to call
    //
    PFN_WDF_DEVICE_PNP_STATE_CHANGE_NOTIFICATION Callback;
};

struct FxPnpStateCallback : public FxCallback {

    FxPnpStateCallback(
        VOID
        ) : FxCallback()
    {
        RtlZeroMemory(&m_Methods[0], sizeof(m_Methods));
    }

    VOID
    Invoke(
        __in WDF_DEVICE_PNP_STATE State,
        __in WDF_STATE_NOTIFICATION_TYPE Type,
        __in WDFDEVICE Device,
        __in PCWDF_DEVICE_PNP_NOTIFICATION_DATA NotificationData
        );

    FxPnpStateCallbackInfo m_Methods[WdfDevStatePnpNull - WdfDevStatePnpObjectCreated];
};

struct FxPowerStateCallbackInfo {
    //
    // Bit field of WDF_STATE_NOTIFICATION_TYPE defined values
    //
    ULONG Types;

    //
    // Function to call
    //
    PFN_WDF_DEVICE_POWER_STATE_CHANGE_NOTIFICATION Callback;
};

struct FxPowerStateCallback : public FxCallback {
    FxPowerStateCallback(
        VOID
        ) : FxCallback()
    {
        RtlZeroMemory(&m_Methods[0], sizeof(m_Methods));
    }

    VOID
    Invoke(
        __in WDF_DEVICE_POWER_STATE State,
        __in WDF_STATE_NOTIFICATION_TYPE Type,
        __in WDFDEVICE Device,
        __in PCWDF_DEVICE_POWER_NOTIFICATION_DATA NotificationData
        );

    FxPowerStateCallbackInfo m_Methods[WdfDevStatePowerNull-WdfDevStatePowerObjectCreated];
};

struct FxPowerPolicyStateCallbackInfo {
    //
    // Bit field of WDF_STATE_NOTIFICATION_TYPE defined values
    //
    ULONG Types;

    //
    // Function to call
    //
    PFN_WDF_DEVICE_POWER_POLICY_STATE_CHANGE_NOTIFICATION Callback;
};

struct FxPowerPolicyStateCallback : public FxCallback {
    FxPowerPolicyStateCallback(
        VOID
        ) : FxCallback()
    {
        RtlZeroMemory(&m_Methods[0], sizeof(m_Methods));
    }

    VOID
    Invoke(
        __in WDF_DEVICE_POWER_POLICY_STATE State,
        __in WDF_STATE_NOTIFICATION_TYPE Type,
        __in WDFDEVICE Device,
        __in PCWDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA NotificationData
        );

    FxPowerPolicyStateCallbackInfo m_Methods[WdfDevStatePwrPolNull-WdfDevStatePwrPolObjectCreated];
};



#endif // _FXPNPCALLBACKS_H_
