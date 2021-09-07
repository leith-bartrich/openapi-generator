/**
 * OpenAPI Petstore
 * This is a sample server Petstore server. For this sample, you can use the api key `special-key` to test the authorization filters.
 *
 * OpenAPI spec version: 1.0.0
 * 
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "OpenAPIPetApiOperations.h"

#include "OpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace OpenAPI
{

FString OpenAPIPetApi::AddPetRequest::ComputePath() const
{
	FString Path(TEXT("/pet"));
	return Path;
}

void OpenAPIPetApi::AddPetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json"), TEXT("application/xml") };
	//static const TArray<FString> Produces = {  };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		WriteJsonValue(Writer, Body);
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Body parameter (body) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Body parameter (body) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::AddPetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 405:
		SetRestResponseDescription(TEXT("Invalid input"));
		break;
	}
}

bool OpenAPIPetApi::AddPetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return true;
}

FString OpenAPIPetApi::DeletePetRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("petId"), ToStringFormatArg(PetId) } };

	FString Path = FString::Format(TEXT("/pet/{petId}"), PathParams);

	return Path;
}

void OpenAPIPetApi::DeletePetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = {  };

	HttpRequest->SetVerb(TEXT("DELETE"));

	// Header parameters
	if (ApiKey.IsSet())
	{
		HttpRequest->SetHeader(TEXT("api_key"), ApiKey.GetValue());
	}

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Form parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);
		Writer->WriteObjectStart();
		Writer->WriteObjectEnd();
		Writer->Close();
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::DeletePetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 400:
		SetRestResponseDescription(TEXT("Invalid pet value"));
		break;
	}
}

bool OpenAPIPetApi::DeletePetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return true;
}

inline FString ToString(const OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum& Value)
{
	switch (Value)
	{
	case OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum::Available:
		return TEXT("available");
	case OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum::Pending:
		return TEXT("pending");
	case OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum::Sold:
		return TEXT("sold");
	}

	UE_LOG(LogOpenAPI, Error, TEXT("Invalid OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIPetApi::FindPetsByStatusRequest::EnumToString(const OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum& Value)
{
	static TMap<FString, OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum> StringToEnum = { 
		{ TEXT("available"), OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum::Available },
		{ TEXT("pending"), OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum::Pending },
		{ TEXT("sold"), OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum::Sold }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIPetApi::FindPetsByStatusRequest::EnumFromString(const FString& EnumAsString, OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline FStringFormatArg ToStringFormatArg(const OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum& Value)
{
	return FStringFormatArg(ToString(Value));
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIPetApi::FindPetsByStatusRequest::StatusEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

FString OpenAPIPetApi::FindPetsByStatusRequest::ComputePath() const
{
	FString Path(TEXT("/pet/findByStatus"));
	TArray<FString> QueryParams;
	QueryParams.Add(FString(TEXT("status=")) + CollectionToUrlString_csv(Status, TEXT("status")));
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void OpenAPIPetApi::FindPetsByStatusRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/xml"), TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Form parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);
		Writer->WriteObjectStart();
		Writer->WriteObjectEnd();
		Writer->Close();
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::FindPetsByStatusResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetRestResponseDescription(TEXT("successful operation"));
		break;
	case 400:
		SetRestResponseDescription(TEXT("Invalid status value"));
		break;
	}
}

bool OpenAPIPetApi::FindPetsByStatusResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPIPetApi::FindPetsByTagsRequest::ComputePath() const
{
	FString Path(TEXT("/pet/findByTags"));
	TArray<FString> QueryParams;
	QueryParams.Add(FString(TEXT("tags=")) + CollectionToUrlString_csv(Tags, TEXT("tags")));
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void OpenAPIPetApi::FindPetsByTagsRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/xml"), TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Form parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);
		Writer->WriteObjectStart();
		Writer->WriteObjectEnd();
		Writer->Close();
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::FindPetsByTagsResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetRestResponseDescription(TEXT("successful operation"));
		break;
	case 400:
		SetRestResponseDescription(TEXT("Invalid tag value"));
		break;
	}
}

bool OpenAPIPetApi::FindPetsByTagsResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPIPetApi::GetPetByIdRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("petId"), ToStringFormatArg(PetId) } };

	FString Path = FString::Format(TEXT("/pet/{petId}"), PathParams);

	return Path;
}

void OpenAPIPetApi::GetPetByIdRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/xml"), TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Form parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);
		Writer->WriteObjectStart();
		Writer->WriteObjectEnd();
		Writer->Close();
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::GetPetByIdResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetRestResponseDescription(TEXT("successful operation"));
		break;
	case 400:
		SetRestResponseDescription(TEXT("Invalid ID supplied"));
		break;
	case 404:
		SetRestResponseDescription(TEXT("Pet not found"));
		break;
	}
}

bool OpenAPIPetApi::GetPetByIdResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPIPetApi::UpdatePetRequest::ComputePath() const
{
	FString Path(TEXT("/pet"));
	return Path;
}

void OpenAPIPetApi::UpdatePetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json"), TEXT("application/xml") };
	//static const TArray<FString> Produces = {  };

	HttpRequest->SetVerb(TEXT("PUT"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		WriteJsonValue(Writer, Body);
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Body parameter (body) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Body parameter (body) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::UpdatePetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 400:
		SetRestResponseDescription(TEXT("Invalid ID supplied"));
		break;
	case 404:
		SetRestResponseDescription(TEXT("Pet not found"));
		break;
	case 405:
		SetRestResponseDescription(TEXT("Validation exception"));
		break;
	}
}

bool OpenAPIPetApi::UpdatePetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return true;
}

FString OpenAPIPetApi::UpdatePetWithFormRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("petId"), ToStringFormatArg(PetId) } };

	FString Path = FString::Format(TEXT("/pet/{petId}"), PathParams);

	return Path;
}

void OpenAPIPetApi::UpdatePetWithFormRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/x-www-form-urlencoded") };
	//static const TArray<FString> Produces = {  };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Form parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);
		Writer->WriteObjectStart();
		if (Name.IsSet()){
			Writer->WriteIdentifierPrefix(TEXT("name"));
			WriteJsonValue(Writer, Name.GetValue());
		}
		if (Status.IsSet()){
			Writer->WriteIdentifierPrefix(TEXT("status"));
			WriteJsonValue(Writer, Status.GetValue());
		}
		Writer->WriteObjectEnd();
		Writer->Close();
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		HttpMultipartFormData FormData;
		if(Name.IsSet())
		{
			FormData.AddStringPart(TEXT("name"), *ToUrlString(Name.GetValue()));
		}
		if(Status.IsSet())
		{
			FormData.AddStringPart(TEXT("status"), *ToUrlString(Status.GetValue()));
		}

		FormData.SetupHttpRequest(HttpRequest);
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		TArray<FString> FormParams;
		if(Name.IsSet())
		{
			FormParams.Add(FString(TEXT("name=")) + ToUrlString(Name.GetValue()));
		}
		if(Status.IsSet())
		{
			FormParams.Add(FString(TEXT("status=")) + ToUrlString(Status.GetValue()));
		}

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded; charset=utf-8"));
		HttpRequest->SetContentAsString(FString::Join(FormParams, TEXT("&")));
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::UpdatePetWithFormResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 405:
		SetRestResponseDescription(TEXT("Invalid input"));
		break;
	}
}

bool OpenAPIPetApi::UpdatePetWithFormResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return true;
}

FString OpenAPIPetApi::UploadFileRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("petId"), ToStringFormatArg(PetId) } };

	FString Path = FString::Format(TEXT("/pet/{petId}/uploadImage"), PathParams);

	return Path;
}

void OpenAPIPetApi::UploadFileRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("multipart/form-data") };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Form parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);
		Writer->WriteObjectStart();
		if (AdditionalMetadata.IsSet()){
			Writer->WriteIdentifierPrefix(TEXT("additionalMetadata"));
			WriteJsonValue(Writer, AdditionalMetadata.GetValue());
		}
		if (File.IsSet()){
			Writer->WriteIdentifierPrefix(TEXT("file"));
			WriteJsonValue(Writer, File.GetValue());
		}
		Writer->WriteObjectEnd();
		Writer->Close();
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		HttpMultipartFormData FormData;
		if(AdditionalMetadata.IsSet())
		{
			FormData.AddStringPart(TEXT("additionalMetadata"), *ToUrlString(AdditionalMetadata.GetValue()));
		}
		if(File.IsSet())
		{
			FormData.AddFilePart(TEXT("file"), File.GetValue());
		}

		FormData.SetupHttpRequest(HttpRequest);
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		TArray<FString> FormParams;
		if(AdditionalMetadata.IsSet())
		{
			FormParams.Add(FString(TEXT("additionalMetadata=")) + ToUrlString(AdditionalMetadata.GetValue()));
		}
		UE_LOG(LogOpenAPI, Error, TEXT("Form parameter (file) was ignored, Files are not supported in urlencoded requests"));

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded; charset=utf-8"));
		HttpRequest->SetContentAsString(FString::Join(FormParams, TEXT("&")));
	}
	else
	{
		UE_LOG(LogOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPetApi::UploadFileResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetRestResponseDescription(TEXT("successful operation"));
		break;
	}
}

bool OpenAPIPetApi::UploadFileResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}
