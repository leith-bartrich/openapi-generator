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

#pragma once

#include "CoreUObject.h"
#include "Json/Public/Json.h"
#include "Json/Public/Serialization/JsonWriter.h"
#include "OpenAPIModule.h"
#include "Helpers.h"
#include "ApiResponse.generated.h"


/*
* ApiResponse Model related types and methods.
*
* Describes the result of uploading an image resource
*/

// declare any enum types



//Blueprint UObject for ApiResponse
UCLASS(BlueprintType)
class OPENAPI_API UOAPIApiResponse : public UOAPIModel
{

    GENERATED_BODY()

public:

    bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) override;
    void WriteJson(JsonWriter& Writer) const override;


    TOptional<int32> Code;

    UFUNCTION(BlueprintCallable)
    const int32 GetCode() const { return this->Code.GetValue(); };

    UFUNCTION(BlueprintCallable)
    void SetCode(int32 In_Code) { this->Code = In_Code; };

    UFUNCTION(BlueprintCallable)
    bool CodeIsSet() const {return this->Code.IsSet();};

    TOptional<FString> Type;

    UFUNCTION(BlueprintCallable)
    const FString GetType() const { return this->Type.GetValue(); };

    UFUNCTION(BlueprintCallable)
    void SetType(FString In_Type) { this->Type = In_Type; };

    UFUNCTION(BlueprintCallable)
    bool TypeIsSet() const {return this->Type.IsSet();};

    TOptional<FString> Message;

    UFUNCTION(BlueprintCallable)
    const FString GetMessage() const { return this->Message.GetValue(); };

    UFUNCTION(BlueprintCallable)
    void SetMessage(FString In_Message) { this->Message = In_Message; };

    UFUNCTION(BlueprintCallable)
    bool MessageIsSet() const {return this->Message.IsSet();};

private:

};



namespace openapi
{

    FString ToString(const UOAPIApiResponse& In_ApiResponse);
    void WriteJsonValue(JsonWriter& Writer, UOAPIApiResponse* Value);

}
