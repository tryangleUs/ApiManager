// Fill out your copyright notice in the Description page of Project Settings.


#include "ApiBluepritnsManager.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpManager.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Async/Async.h"
#include "GenericPlatform/GenericPlatformProcess.h"

UApiBluepritnsManager* thisObjRef;
FString PrintResponse = "";
FJsonObject ReturnValue;
FTimerHandle TimerHandle;
const UObject* WorldContextObjectRef;
FString ConnectionToken;


// generic url for all //
FString basicUrl = "https://api.tryangle.us";

// Constructor for initializing values //
UApiBluepritnsManager::UApiBluepritnsManager() {
	thisObjRef = this;
}

// Functional Apis //
FString UApiBluepritnsManager::GetGameInfo(int gameId, const UObject* WorldContextObject)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);

	WorldContextObjectRef = WorldContextObject;
	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetNumberField("gameId", gameId);

	Request->SetURL(basicUrl + "/GetGameInfo");
	Request->SetVerb("POST");

	FString JsonString;

	// sending data in the body //
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);

	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetContentAsString(JsonString);
	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);
	UE_LOG(LogTemp, Warning, TEXT("Hello the request worked fine"));

	return PrintResponse;

}

FString UApiBluepritnsManager::GetERC721BalanceByOwner(int gameId, FString ownerAddressString)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetNumberField("gameId", gameId);
	RequestObject->SetStringField("owner", ownerAddressString);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/GetERC721BalanceByOwner");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}

FString UApiBluepritnsManager::GetERC721TokenByOwner(FString ERC721Token, int startIndex, int endIndex, FString ownerAddressString)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetStringField("ERC721", ERC721Token);
	RequestObject->SetNumberField("startIndex", startIndex);
	RequestObject->SetNumberField("endIndex", endIndex);
	RequestObject->SetStringField("owner", ownerAddressString);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/GetERC721TokenByOwner");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}

FString UApiBluepritnsManager::GetERC20AllowedByOwner(int gameId, FString ownerAddressString)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetNumberField("gameId", gameId);
	RequestObject->SetStringField("owner", ownerAddressString);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	basicUrl.Append("/GetERC20AllowedByOwner");

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/GetERC20AllowedByOwner");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}

FString UApiBluepritnsManager::GetERC20BalanceByOwner(int gameId, FString ownerAddressString)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetNumberField("gameId", gameId);
	RequestObject->SetStringField("owner", ownerAddressString);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/GetERC20BalanceByOwner");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}

FString UApiBluepritnsManager::GetTxStatus(FString txHash)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetStringField("txHash", txHash);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/GetTxStatus");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}

FString UApiBluepritnsManager::GetERC721Metadata(FString ERC721, FString tokenId)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetStringField("ERC721", ERC721);
	RequestObject->SetStringField("tokenId", tokenId);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/GetERC721Metadata");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}
// Functional Apis //

// Authentication  Apis //
FString UApiBluepritnsManager::GetConnectionUrl(const UObject* WorldContextObject)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnGetConnectionResponce);

	WorldContextObjectRef = WorldContextObject;

	Request->SetURL(basicUrl + "/GetConnectionUrl");
	Request->SetVerb("POST");

	Request->GetResponse();
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}

FString UApiBluepritnsManager::GetAuthentication(FString connectionToken, const UObject* WorldContextObject)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::CheckAuthResponce);

	WorldContextObjectRef = WorldContextObject;
	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetStringField("connectionToken", connectionToken);
	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->SetURL(basicUrl + "/GetAuth");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	return PrintResponse;
}
// Authentication  Apis //

// Transfer Apis //
FString UApiBluepritnsManager::TransferERC721(int gameId, FString ERC721Token, int tokenId, FString ownerAddressString, FString recipientAddressString)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetNumberField("gameId", gameId);
	RequestObject->SetStringField("ERC721", ERC721Token);
	RequestObject->SetNumberField("tokenId", tokenId);
	RequestObject->SetStringField("owner", ownerAddressString);
	RequestObject->SetStringField("recipient", recipientAddressString);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/TransferERC721");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}

FString UApiBluepritnsManager::TransferERC20(int gameId, FString ERC20Token, int amount, FString ownerAddressString, FString recipientAddressString)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// creating a body to send //
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetNumberField("gameId", gameId);
	RequestObject->SetStringField("ERC20", ERC20Token);
	RequestObject->SetNumberField("amount", amount);
	RequestObject->SetStringField("owner", ownerAddressString);
	RequestObject->SetStringField("recipient", recipientAddressString);

	// sending data in the body //
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RequestObject, Writer);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(thisObjRef, &UApiBluepritnsManager::OnResponseReceived);
	Request->SetURL(basicUrl + "/TransferERC20");
	Request->SetVerb("POST");

	Request->ProcessRequest();

	FHttpModule::Get().GetHttpManager().Flush(false);

	return PrintResponse;
}


/*Assigned function on successfull http call*/
void UApiBluepritnsManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("Responce received in On Responce Received %s"), *Response->GetContentAsString());
	PrintResponse = *Response->GetContentAsString();
	if (Response->GetResponseCode() == 200) {
		//Create a pointer to hold the json serialized data
		TSharedPtr<FJsonObject> JsonObject;

		//Create a reader pointer to read the json data
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		//Deserialize the json data given Reader and the actual object to deserialize
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			ReturnValue.SetObjectField("Values", JsonObject);
			//Get the value of the json object by field name
			int32 recievedInt = JsonObject->GetIntegerField("customInt");

			//Output it to the engine
			GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Responce from api is %s"), *Response->GetContentAsString());
	}
}

void UApiBluepritnsManager::OnGetConnectionResponce(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("Responce received in On Responce Received %s"), *Response->GetContentAsString());
	PrintResponse = *Response->GetContentAsString();
	if (Response->GetResponseCode() == 200) {
		//Create a pointer to hold the json serialized data
		TSharedPtr<FJsonObject> JsonObject;

		//Create a reader pointer to read the json data
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		//Deserialize the json data given Reader and the actual object to deserialize
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString url;
			ReturnValue.SetObjectField("Values", JsonObject);
			//Get the value of the json object by field name

			url = JsonObject->GetStringField("url");
			ConnectionToken = JsonObject->GetStringField("connectionToken");
			if (!url.IsEmpty()) {
				int32 recievedInt = JsonObject->GetIntegerField("customInt");
				FPlatformProcess::LaunchURL(*url, NULL, NULL);
				//Output it to the engine
				GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
			}
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Responce from api is %s"), *Response->GetContentAsString());
	}
}

void UApiBluepritnsManager::CheckAuthResponce(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	PrintResponse = *Response->GetContentAsString();
	if (Response->GetResponseCode() == 200) {
		//Create a pointer to hold the json serialized data
		TSharedPtr<FJsonObject> JsonObject;

		const FString ResponseBody = Response->GetContentAsString();
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			float timepassed;
			FString address;

			address = JsonObject->GetStringField("address");
			timepassed = WorldContextObjectRef->GetWorld()->GetRealTimeSeconds();

			if (address.IsEmpty()) {
				WorldContextObjectRef->GetWorld()->GetTimerManager().SetTimer(TimerHandle, thisObjRef, &UApiBluepritnsManager::CallingAuthAfterDelay, 2.0f, true);
				if (timepassed >= 120) {
					WorldContextObjectRef->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("Responce is not null %s"), *address);
				WorldContextObjectRef->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Responce from api is %s"), *Response->GetContentAsString());
	}
}

void UApiBluepritnsManager::ConnectionFunction()
{
	GetAuthentication(ConnectionToken, WorldContextObjectRef);
	WorldContextObjectRef->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UApiBluepritnsManager::CallingAuthAfterDelay()
{
	GetAuthentication(ConnectionToken, WorldContextObjectRef);
}

void UApiBluepritnsManager::WaitingForData()
{
	if (PrintResponse.IsEmpty()) {
		WorldContextObjectRef->GetWorld()->GetTimerManager().SetTimer(TimerHandle, thisObjRef, &UApiBluepritnsManager::WaitingForData, 3.0f, true);

	}
	else {
		WorldContextObjectRef->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

