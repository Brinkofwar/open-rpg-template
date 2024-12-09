// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define EARBITRARY_MACRO(ClassName) \
	void ClassName::SArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) \
	{ \
		CArbitraryRequest(ChannelID, Parameters); \
	} \
	bool ClassName::SArbitraryRequest_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters) \
	{ \
		return ChannelID.IsValid(); \
	} \
	void ClassName::CArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) \
	{ \
		OnArbitraryRequest.Broadcast(ChannelID, Parameters); \
	} \
	void ClassName::SArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) \
	{ \
		CArbitraryResponse(ChannelID, Parameters); \
	} \
	bool ClassName::SArbitraryResponse_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters) \
	{ \
		return ChannelID.IsValid(); \
	} \
	void ClassName::CArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) \
	{ \
		OnArbitraryResponse.Broadcast(ChannelID, Parameters); \
	} \
	void ClassName::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {} \
	void ClassName::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {} \


#define EGAMEPLAYTAG_MACRO(ClassName) \
	void ClassName::SAddGameplayTag_Implementation(FGameplayTag Tag) \
	{ \
		CAddGameplayTag(Tag); \
	} \
	bool ClassName::SAddGameplayTag_Validate(FGameplayTag Tag) \
	{ \
		return Tag.IsValid(); \
	} \
	void ClassName::CAddGameplayTag_Implementation(FGameplayTag Tag) \
	{ \
		OnTagAdded.Broadcast(Tag); \
	} \
	void ClassName::SRemoveGameplayTag_Implementation(FGameplayTag Tag) \
	{ \
		CRemoveGameplayTag(Tag); \
	} \
	bool ClassName::SRemoveGameplayTag_Validate(FGameplayTag Tag) \
	{ \
		return Tag.IsValid(); \
	} \
	void ClassName::CRemoveGameplayTag_Implementation(FGameplayTag Tag) \
	{ \
		OnTagRemoved.Broadcast(Tag); \
	}