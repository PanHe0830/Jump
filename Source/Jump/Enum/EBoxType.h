// ���Ⱥ�ţ��

#pragma once

UENUM(BlueprintType)
enum class EBoxType : uint8
{
	ERectangle UMETA(DisplayName = "Rectangle"), // ����
	EGarden UMETA(DisplayName = "Garden"),	// Բ��

	EDefault UMETA(DisplayName = "default")
};