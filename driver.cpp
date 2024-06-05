#include <ntddk.h>

#define DEVICE_NAME         L"\\Device\\IoctlDriver"
#define LINK_NAME           L"\\DosDevices\\IoctlDriver"

UNICODE_STRING deviceName;
UNICODE_STRING symbolicLinkName;
PDEVICE_OBJECT g_DeviceObject;

NTSTATUS DriverUnload(PDRIVER_OBJECT DriverObject) {
    IoDeleteSymbolicLink(&symbolicLinkName);
    IoDeleteDevice(g_DeviceObject);
    KdPrint(("Driver Unloaded\n"));
    return STATUS_SUCCESS;
}

NTSTATUS DeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PIO_STACK_LOCATION irpStack;
    NTSTATUS status = STATUS_SUCCESS;

    irpStack = IoGetCurrentIrpStackLocation(Irp);

    switch (irpStack->Parameters.DeviceIoControl.IoControlCode) {
        default:
            status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    Irp->IoStatus.Status = status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return status;
}

NTSTATUS DriverDispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PIO_STACK_LOCATION irpStack;
    NTSTATUS status = STATUS_SUCCESS;

    irpStack = IoGetCurrentIrpStackLocation(Irp);

    switch (irpStack->MajorFunction) {
        case IRP_MJ_CREATE:
            break;
        case IRP_MJ_CLOSE:
            break;
        case IRP_MJ_DEVICE_CONTROL:
            status = DeviceControl(DeviceObject, Irp);
            break;
        default:
            break;
    }

    Irp->IoStatus.Status = status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return status;
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    NTSTATUS status;

    DriverObject->DriverUnload = DriverUnload;

    RtlInitUnicodeString(&deviceName, DEVICE_NAME);
    RtlInitUnicodeString(&symbolicLinkName, LINK_NAME);

    status = IoCreateDevice(DriverObject, 0, &deviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &g_DeviceObject);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    status = IoCreateSymbolicLink(&symbolicLinkName, &deviceName);
    if (!NT_SUCCESS(status)) {
        IoDeleteDevice(DriverObject->DeviceObject);
        return status;
    }

    DriverObject->MajorFunction[IRP_MJ_CREATE] = DriverObject->MajorFunction[IRP_MJ_CLOSE] = DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DriverDispatch;

    KdPrint(("Driver Loaded\n"));

    return STATUS_SUCCESS;
}
