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

#include "Category.h"

#include "OpenAPIModule.h"

#include "Templates/SharedPointer.h"







void UOAPICategory::WriteJson(JsonWriter& Writer) const
{
    Writer->WriteObjectStart();
    if (Id.IsSet())
    {
        Writer->WriteIdentifierPrefix(TEXT("id")); openapi::WriteJsonValue(Writer, Id.GetValue());
    }
    if (Name.IsSet())
    {
        Writer->WriteIdentifierPrefix(TEXT("name")); openapi::WriteJsonValue(Writer, Name.GetValue());
    }
    Writer->WriteObjectEnd();
}

bool UOAPICategory::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
    const TSharedPtr<FJsonObject>* Object;
    if (!JsonValue->TryGetObject(Object))
        return false;

    bool ParseSuccess = true;

    ParseSuccess &= openapi::TryGetJsonValue(*Object, TEXT("id"), Id);
    ParseSuccess &= openapi::TryGetJsonValue(*Object, TEXT("name"), Name);

    return ParseSuccess;
}



namespace openapi
{

    FString ToString(const UOAPICategory& In_Category)
    {
        FString String;
        JsonWriter Writer = TJsonWriterFactory<>::Create(&String);
        In_Category.WriteJson(Writer);
        Writer->Close();
        return String;
    }

    void WriteJsonValue(JsonWriter& Writer, UOAPICategory* Value){
        Value->WriteJson(Writer);
    }

}
