// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Interfaces/IHttpRequest.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "ApiBluepritnsManager.generated.h"
/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestEvent);

UCLASS(Config = Game)
class APIMANAGER_API UApiBluepritnsManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UPROPERTY(Config)
		FString GetGameInfoUrlPath;

public:

	FHttpModule* Http;
	FTimerHandle TimerHandle;

	UApiBluepritnsManager();

	// Functional Apis 
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetGameInfo(int gameId, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetERC721BalanceByOwner(int gameId, FString ownerAddressString);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetERC721TokenByOwner(FString ERC721Token, int startIndex, int endIndex, FString ownerAddressString);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetERC20AllowedByOwner(int gameId, FString ownerAddressString);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetERC20BalanceByOwner(int gameId, FString ownerAddressString);
	
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetTxStatus(FString txHash);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetERC721Metadata(FString ERC721, FString tokenId);

	// Authentication  Apis
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetConnectionUrl(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Custom Utilities")
		static FString GetAuthentication(FString connectionToken, const UObject* WorldContextObject);

	// Transfer Apis
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString TransferERC721(int gameId, FString ERC721Token, int tokenId, FString ownerAddressString, FString recipientAddressString);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = "Custom Utilities")
		static FString TransferERC20(int gameId, FString ERC20Token, int amount, FString ownerAddressString, FString recipientAddressString);

	// Return a Responce value
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnGetConnectionResponce(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void CheckAuthResponce(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void ConnectionFunction();

	void CallingAuthAfterDelay();

	void WaitingForData();

};
