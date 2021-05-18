// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ArchWalk/ArchWalkGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeArchWalkGameModeBase() {}
// Cross Module References
	ARCHWALK_API UClass* Z_Construct_UClass_AArchWalkGameModeBase_NoRegister();
	ARCHWALK_API UClass* Z_Construct_UClass_AArchWalkGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ArchWalk();
// End Cross Module References
	void AArchWalkGameModeBase::StaticRegisterNativesAArchWalkGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AArchWalkGameModeBase_NoRegister()
	{
		return AArchWalkGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AArchWalkGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AArchWalkGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ArchWalk,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArchWalkGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "ArchWalkGameModeBase.h" },
		{ "ModuleRelativePath", "ArchWalkGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AArchWalkGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AArchWalkGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AArchWalkGameModeBase_Statics::ClassParams = {
		&AArchWalkGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AArchWalkGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AArchWalkGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AArchWalkGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AArchWalkGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AArchWalkGameModeBase, 3165145440);
	template<> ARCHWALK_API UClass* StaticClass<AArchWalkGameModeBase>()
	{
		return AArchWalkGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AArchWalkGameModeBase(Z_Construct_UClass_AArchWalkGameModeBase, &AArchWalkGameModeBase::StaticClass, TEXT("/Script/ArchWalk"), TEXT("AArchWalkGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AArchWalkGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
