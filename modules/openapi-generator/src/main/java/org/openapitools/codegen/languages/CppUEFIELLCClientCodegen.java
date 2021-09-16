/*
 * Copyright 2018 OpenAPI-Generator Contributors (https://openapi-generator.tech)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//originally branched from the cpp-ue4 Codegen

package org.openapitools.codegen.languages;

import io.swagger.v3.oas.models.media.ArraySchema;
import io.swagger.v3.oas.models.media.Schema;
import io.swagger.v3.parser.util.SchemaTypeUtil;
import org.openapitools.codegen.CliOption;
import org.openapitools.codegen.CodegenConstants;
import org.openapitools.codegen.CodegenType;
import org.openapitools.codegen.SupportingFile;
import org.openapitools.codegen.meta.GeneratorMetadata;
import org.openapitools.codegen.meta.Stability;
import org.openapitools.codegen.utils.ModelUtils;

import java.io.File;
import java.util.*;

import static org.openapitools.codegen.utils.StringUtils.camelize;

public class CppUEFIELLCClientCodegen extends AbstractCppCodegen {

    //command line strings

    public static final String CPP_NAMESPACE_FLAG_NAME = "cppNamespace";
    public static final String CPP_NAMESPACE_FLAG_DESC = "C++ namespace for non Unreal classes (convention: name::space::for::api).";
    public static final String UNREAL_MODULE_NAME_FLAG_NAME = "unrealModuleName";
    public static final String UNREAL_MODULE_NAME_FLAG_DESC = "Name of the generated unreal module (optional)";
    public static final String UNREAL_MODULE_PREFIX_FLAG_NAME = "unrealModulePrefix";
    public static final String UNREAL_MODULE_PREFIX_FLAG_DESC = "short prefix string for the head of Unreal classes (e.g. FPL would change UApi to UFPLApi";
    public static final String UNREAL_MAKE_MODULE_FILES_FLAG_NAME = "makeModule";
    public static final String UNREAL_MAKE_MODULE_FILES_FLAG_DESC = "Generate module .h and .cpp files.";
    public static final String UNREAL_MAKE_BUILD_FILE_FLAG_NAME = "makeBuildCS";
    public static final String UNREAL_MAKE_BUILD_FILE_FLAG_DESC = "Generate Build.cs file";

    //command line vars and their defaults
    protected String cppNamespace = "openapi";
    protected String unrealModuleName = "OpenAPI";
    protected String unrealModulePrefix = "OAPI";
    protected boolean unrealMakeModuleFiles = true;
    protected boolean unrealMakeBuildFile = true;


    //generator configuration

    //const values
    protected String privateFolder = "Private";
    protected String publicFolder = "Public";
    protected String apiVersion = "1.0.0";

    //vars
    protected Set<String> pointerClasses = new HashSet<String>();     // Will be treated as pointer
    protected Map<String, String> namespaces = new HashMap<String, String>();  // Will be included using the <> syntax, not used in Unreal's coding convention
    protected Set<String> systemIncludes = new HashSet<String>();      // ^

    public CppUEFIELLCClientCodegen() {
        super();

        this.generatorMetadata = GeneratorMetadata.newBuilder(generatorMetadata)
                .stability(Stability.EXPERIMENTAL)
                .build();

        //propogate CLI defaults to additional params
        //they will be overwritten by CLI values if specified.
        this.additionalProperties.put(CPP_NAMESPACE_FLAG_NAME,cppNamespace);
        this.additionalProperties.put(UNREAL_MODULE_NAME_FLAG_NAME,unrealModuleName);
        this.additionalProperties.put(UNREAL_MODULE_PREFIX_FLAG_NAME,unrealModulePrefix);
        this.additionalProperties.put(UNREAL_MAKE_BUILD_FILE_FLAG_NAME, unrealMakeBuildFile);
        this.additionalProperties.put(UNREAL_MAKE_MODULE_FILES_FLAG_NAME, unrealMakeModuleFiles);

        this.additionalProperties.put("apiVersion", this.apiVersion);

        // set the output folder here
        this.outputFolder = "generated-code/cpp-ue-fiellc";

        /*
         * Models.  You can write model files using the modelTemplateFiles map.
         * if you want to create one template for file, you can do so here.
         * for multiple files for model, just put another entry in the `modelTemplateFiles` with
         * a different extension
         */
        this.modelTemplateFiles.put(
                "model-header.mustache",
                ".h");

        this.modelTemplateFiles.put(
                "model-source.mustache",
                ".cpp");

        /*
         * Api classes.  You can write classes for each Api file with the apiTemplateFiles map.
         * as with models, add multiple entries with different extensions for multiple files per
         * class
         */
        this.apiTemplateFiles.put(
                "api-header.mustache",   // the template to use
                ".h");       // the extension for each file to write

        this.apiTemplateFiles.put(
                "api-source.mustache",   // the template to use
                ".cpp");       // the extension for each file to write


        /*
         * Supporting files.
         */
        this.supportingFiles.add(new SupportingFile("helpers-header.mustache", publicFolder,  "Helpers.h"));


        /*
         * Template Location.  This is the location which templates will be read from.  The generator
         * will use the resource stream to attempt to read the templates.
         */
        this.embeddedTemplateDir = templateDir = "cpp-ue-fiellc";


        /*
         * Language Specific Primitives.  These types will not trigger imports by
         * the client generator
         */
        this.languageSpecificPrimitives = new HashSet<String>(
                Arrays.asList(
                        "bool",
                        "int32",
                        "int64",
                        "float",
                        "double",
                        "FString",
                        "FDateTime",
                        "FGuid",
                        "TArray",
                        "TArray<uint8>",  // For byte arrays
                        "TMap",
                        "TSharedPtr<FJsonObject>",
                        "TSharedPtr<FJsonValue>")
        );


        // Maps C++ types during call to getSchemaType, see DefaultCodegen.getSchemaType and not the types/formats
        // defined in openapi specification "array" is also used explicitly in the generator for containers
        super.typeMapping = new HashMap<String, String>();
        typeMapping.clear();
        typeMapping.put("integer", "int32");
        typeMapping.put("long", "int64");
        typeMapping.put("float", "float");
        typeMapping.put("number", "double");
        typeMapping.put("double", "double");
        typeMapping.put("string", "FString");
        typeMapping.put("byte", "uint8");
        typeMapping.put("binary", "TArray<uint8>");
        typeMapping.put("ByteArray", "TArray<uint8>");
        typeMapping.put("password", "FString");
        typeMapping.put("boolean", "bool");
        typeMapping.put("date", "FDateTime");
        typeMapping.put("Date", "FDateTime");
        typeMapping.put("date-time", "FDateTime");
        typeMapping.put("DateTime", "FDateTime");
        typeMapping.put("array", "TArray");
        typeMapping.put("list", "TArray");
        typeMapping.put("map", "TMap");
        typeMapping.put("object", "TSharedPtr<FJsonObject>");
        typeMapping.put("Object", "TSharedPtr<FJsonObject>");
        typeMapping.put("file", "HttpFileInput");
        typeMapping.put("UUID", "FGuid");
        typeMapping.put("AnyType", "TSharedPtr<FJsonValue>");

        importMapping = new HashMap<String, String>();
        //importMapping.put("HttpFileInput", "#include \"" + this.modelNamePrefix + "Helpers.h\"");

        namespaces = new HashMap<String, String>();

    }

    private void setupOptionalTemplateFiles() {

        if (unrealMakeModuleFiles) {
            supportingFiles.add(new SupportingFile("module-header.mustache", publicFolder, unrealModuleName + "Module.h"));
            supportingFiles.add(new SupportingFile("module-source.mustache", privateFolder, unrealModuleName + "Module.cpp"));
        }

        if(unrealMakeBuildFile){
            supportingFiles.add(new SupportingFile("Build.cs.mustache", unrealModuleName + ".Build.cs"));
        }
    }


    @Override
    public void processOpts() {
        super.processOpts();

        //get cli values
        this.cppNamespace = (String) this.additionalProperties.get(CPP_NAMESPACE_FLAG_NAME);
        this.unrealModuleName = (String) this.additionalProperties.get(UNREAL_MODULE_NAME_FLAG_NAME);
        this.unrealModulePrefix = (String) this.additionalProperties.get(UNREAL_MODULE_PREFIX_FLAG_NAME);
        this.unrealMakeBuildFile = (boolean) this.additionalProperties.get(UNREAL_MAKE_BUILD_FILE_FLAG_NAME);
        this.unrealMakeModuleFiles = (boolean) this.additionalProperties.get(UNREAL_MAKE_MODULE_FILES_FLAG_NAME);

        //also set a list of nested namespaces by the split string.
        additionalProperties.put(CPP_NAMESPACE_FLAG_NAME + "Declarations", this.cppNamespace.split("\\::"));

        //set the unreal API marker name
        this.additionalProperties.put("dllapi", unrealModuleName.toUpperCase(Locale.ROOT) + "_API");

        setupOptionalTemplateFiles();

    }


    /**
     * Configures the type of generator.
     *
     * @return the CodegenType for this generator
     * @see CodegenType
     */
    @Override
    public CodegenType getTag() {
        return CodegenType.CLIENT;
    }

    /**
     * Configures a friendly name for the generator.  This will be used by the generator
     * to select the library with the -l flag.
     *
     * @return the friendly name for the generator
     */
    @Override
    public String getName() {
        return "cpp-ue-fiellc";
    }

    /**
     * Returns human-friendly help for the generator.  Provide the consumer with help
     * tips, parameters here
     *
     * @return A string value for the help message
     */
    @Override
    public String getHelp() {
        return "Generates a Unreal Engine C++ Module (EXPERIMENTAL).";
    }



    @Override
    public String toModelImport(String name) {
        if (namespaces.containsKey(name)) {
            return "using " + namespaces.get(name) + ";";
        } else if (systemIncludes.contains(name)) {
            return "#include <" + name + ">";
        }

        String folder = modelPackage().replace("::", File.separator);
        if (!folder.isEmpty())
            folder += File.separator;

        return "#include \"" + folder + name + ".h\"";
    }

    @Override
    protected boolean needToImport(String type) {
        boolean shouldImport = super.needToImport(type);
        if (shouldImport)
            return !languageSpecificPrimitives.contains(type);
        else
            return false;
    }

    /**
     * Escapes a reserved word as defined in the `reservedWords` array. Handle escaping
     * those terms here.  This logic is only called if a variable matches the reserved words
     *
     * @return the escaped term
     */
    @Override
    public String escapeReservedWord(String name) {
        if (this.reservedWordsMappings().containsKey(name)) {
            return this.reservedWordsMappings().get(name);
        }
        return "_" + name;
    }

    /**
     * Location to write model files.
     */
    @Override
    public String modelFileFolder() {
        return outputFolder + File.separator;
    }

    /**
     * Location to write api files.
     */
    @Override
    public String apiFileFolder()
    {
        return outputFolder + File.separator ;
    }


    @Override
    public String modelFilename(String templateName, String modelName) {
        //reverse lookup to get the requested suffix.
        String suffix = this.modelTemplateFiles().get(templateName);

        //set folder based on .h or .cpp
        String folder = privateFolder;
        if (suffix.endsWith(".h")) {
            folder = publicFolder;
        }

        return this.modelFileFolder() + File.separator + folder + File.separator + toModelFilename(modelName) + suffix;
    }

    @Override
    public String toModelFilename(String name) {
        name = sanitizeName(name);
        return camelize(name);
    }

    @Override
    public String apiFilename(String templateName, String tag) {
        //reverse lookup to get the requested suffix.
        String suffix = apiTemplateFiles().get(templateName);

        //set folder based on .h or .cpp
        String folder = privateFolder;
        if (suffix.endsWith(".h")) {
            folder = publicFolder;
        }

        return apiFileFolder() + File.separator + folder + File.separator + toApiFilename(tag) + suffix;
    }

    @Override
    public String toApiFilename(String name) {
        name = sanitizeName(name);
        return camelize(name) + "Api";
    }


    /**
     * Optional - type declaration.  This is a String which is used by the templates to instantiate your
     * types.  There is typically special handling for different property types
     *
     * @return a string value used as the `dataType` field for model templates, `returnType` for api templates
     */
    @Override
    public String getTypeDeclaration(Schema p) {
        String openAPIType = getSchemaType(p);

        if (ModelUtils.isArraySchema(p)) {
            ArraySchema ap = (ArraySchema) p;
            String inner = getSchemaType(ap.getItems());
            return getSchemaType(p) + "<" + getTypeDeclaration(inner) + ">";
        } else if (ModelUtils.isMapSchema(p)) {
            String inner = getSchemaType(getAdditionalProperties(p));
            return getSchemaType(p) + "<FString, " + getTypeDeclaration(inner) + ">";
        }

        if (pointerClasses.contains(openAPIType)) {
            return openAPIType + "*";
        } else if (languageSpecificPrimitives.contains(openAPIType)) {
            return toModelName(openAPIType);
        } else {
            return openAPIType;
        }
    }

    @Override
    public String getTypeDeclaration(String name) {
        return name;
    }

    @Override
    public String toDefaultValue(Schema p) {
        if (ModelUtils.isStringSchema(p)) {
            if (p.getDefault() != null) {
                return "TEXT(\"" + p.getDefault().toString() + "\")";
            } else {
                return null;
            }
        } else if (ModelUtils.isBooleanSchema(p)) {
            if (p.getDefault() != null) {
                return p.getDefault().toString();
            } else {
                return "false";
            }
        } else if (ModelUtils.isDateSchema(p)) {
            return "FDateTime(0)";
        } else if (ModelUtils.isDateTimeSchema(p)) {
            return "FDateTime(0)";
        } else if (ModelUtils.isDoubleSchema(p)) {
            if (p.getDefault() != null) {
                return p.getDefault().toString();
            } else {
                return "0.0";
            }
        } else if (ModelUtils.isFloatSchema(p)) {
            if (p.getDefault() != null) {
                return p.getDefault().toString();
            } else {
                return "0.0f";
            }
        } else if (ModelUtils.isIntegerSchema(p)) {
            if (p.getDefault() != null) {
                return p.getDefault().toString();
            } else {
                return "0";
            }
        } else if (ModelUtils.isLongSchema(p)) {
            if (p.getDefault() != null) {
                return p.getDefault().toString();
            } else {
                return "0";
            }
        }

        return null;
    }

    /**
     * Optional - OpenAPI type conversion.  This is used to map OpenAPI types in a `Property` into
     * either language specific types via `typeMapping` or into complex models if there is not a mapping.
     *
     * @return a string value of the type or complex model for this property
     * @see Schema
     */
    @Override
    public String getSchemaType(Schema p) {
        String openAPIType = super.getSchemaType(p);
        String type = null;
        if (typeMapping.containsKey(openAPIType)) {
            type = typeMapping.get(openAPIType);
            if (languageSpecificPrimitives.contains(type)) {
                return toModelName(type);
            }
            if (pointerClasses.contains(type)) {
                return type;
            }
        } else {
            type = openAPIType;
        }
        return toModelName(type);
    }

    @Override
    public String toModelName(String type) {
        if (typeMapping.keySet().contains(type) ||
                typeMapping.values().contains(type) ||
                importMapping.values().contains(type) ||
                defaultIncludes.contains(type) ||
                languageSpecificPrimitives.contains(type)) {
            return type;
        } else {
            return camelize(sanitizeName(type), false);
        }
    }

    @Override
    public String toVarName(String in_name) {
        // sanitize name
        String name = sanitizeName(in_name);

        // if it's all upper case, convert to lower case
        if (name.matches("^[A-Z_]*$")) {
            name = name.toLowerCase(Locale.ROOT);
        }

        //Unreal variable names are CamelCase
        String camelCaseName = camelize(name, false);

        //Avoid empty variable name at all costs
        if(!camelCaseName.isEmpty()) {
            name = camelCaseName;
        }

        // for reserved word or word starting with number, append _
        if (isReservedWord(name) || name.matches("^\\d.*")) {
            name = escapeReservedWord(name);
        }

        return name;
    }

    @Override
    public String toEnumVarName(String name, String datatype) {
        return toVarName(name);
    }

    @Override
    public String toParamName(String name) {
        return toVarName(name);
    }

    @Override
    public String toApiName(String type) {
        return camelize(type, false) + "Api";
    }

    @Override
    public String escapeQuotationMark(String input) {
        // remove " to avoid code injection
        return input.replace("\"", "");
    }

    @Override
    public String escapeUnsafeCharacters(String input) {
        return input.replace("*/", "*_/").replace("/*", "/_*");
    }

    @Override
    public String toBooleanGetter(String name) {
        return "Is" + getterAndSetterCapitalize(name);
    }

    @Override
    public String toGetter(String name) {
        return "Get" + getterAndSetterCapitalize(name);
    }

    @Override
    public String toSetter(String name) {
        return "Set" + getterAndSetterCapitalize(name);
    }
}
