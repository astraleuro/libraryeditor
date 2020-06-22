#ifndef DEFINES_H
#define DEFINES_H

#define SEPARATOR "|"

#define APPLICATION_NAME  "LEditor"
#define APPLICATION_MAJOR_VERSION "1"
#define APPLICATION_MINOR_VERSION "0"
#define APPLICATION_BUGFIX_VERSION "3"
#define APPLICATION_VERSION_SUFFIX ""
#define APPLICATION_VERSION APPLICATION_MAJOR_VERSION "." \
                            APPLICATION_MINOR_VERSION "." \
                            APPLICATION_BUGFIX_VERSION " " \
                            APPLICATION_VERSION_SUFFIX

#define PROGRAM_AUTHOR_NAME "Кирилл Зимин (astral.euro@gmail.com)"
#define PROGRAM_NAME APPLICATION_NAME " - управление данными приложения «Пазлы-Живопись»\n" \
    "Версия: " APPLICATION_VERSION "\n" "Автор: " PROGRAM_AUTHOR_NAME

#define MAINWINDOW_TITLE APPLICATION_NAME " " APPLICATION_VERSION

#define CONFIG_FILE APPLICATION_NAME "_" APPLICATION_MAJOR_VERSION "." APPLICATION_MINOR_VERSION "." APPLICATION_BUGFIX_VERSION ".conf"

#define BASE_EXTENSION ".ledb"
#define BASE_EXTENSION_FILTER "*" BASE_EXTENSION
#define IMAGE_EXTENSION_FILTER "*.jpg *.png" SEPARATOR "*.jpg" SEPARATOR "*.png"

#define WELCOME_OPENFILE_TITLE_KEY "openFileTitle"
#define WELCOME_OPENFILE_TITLE "Открыть..."
#define WELCOME_SAVEFILE_TITLE_KEY "saveFileTitle"
#define WELCOME_SAVEFILE_TITLE "Сохранить..."

#define ARTS_KEY "arts"
#define ARTS_LABEL "Предметы искусства"
#define ARTS_OPTIONS_KEY "artsOptions"

#define AUTHORS_KEY "authors"
#define AUTHORS_LABEL "Авторы"
#define AUTHORS_OPTIONS_KEY "authorsOptions"

#define ERAS_KEY "eras"
#define ERAS_LABEL "Эпохи"
#define ERAS_OPTIONS_KEY "erasOptions"

#define FILE_SECTION_KEY "artPath" SEPARATOR "authorImagePath" SEPARATOR "eraImagePath"
#define ARRAY_SECTION_KEY "arts" SEPARATOR "authors" SEPARATOR "eras"
#define UNIQUE_SECTION_KEY "artName" SEPARATOR "authorName" SEPARATOR "eraName"
#define NEWESTBY_SECTION_KEY "lastUpdate"

#define FILTER_VISIBLE_KEY "filterVisible"
#define FILTER_TEXT_KEY "filterData"

#define SORT_VISIBLE_KEY "sortVisible"
#define SORT_TEXT_KEY "sortData"
#define SORT_ORDER_KEY "sortOrder"

#define IMAGE_WIDTH_KEY "imageWidth"

#define TEXT_COLS_H_KEY "textHeaderCols"
#define TEXT_COLS_F_KEY "textFooterCol"

#define ARTS_TEXT_COLS_H "artName" SEPARATOR "artAuthors" SEPARATOR "artEra" SEPARATOR "isDomestic" SEPARATOR "artInfo"
#define ARTS_TEXT_COLS_F "lastUpdate"

#define AUTHORS_TEXT_COLS_H "authorName" SEPARATOR "authorInfo"
#define AUTHORS_TEXT_COLS_F "lastUpdate"

#define ERAS_TEXT_COLS_H "eraName"
#define ERAS_TEXT_COLS_F "lastUpdate"

#define TEXT_COLS_LABELS_KEY "itemKeyLabels"

#define ARTS_TEXT_COLS_LABELS "Название" SEPARATOR "artName" \
    SEPARATOR "Категория" SEPARATOR "isDomestic" \
    SEPARATOR "Эпоха" SEPARATOR "artEra" \
    SEPARATOR "Авторы" SEPARATOR "artAuthors" \
    SEPARATOR "Информация" SEPARATOR "artInfo" \
    SEPARATOR "Дата" SEPARATOR "lastUpdate"

#define AUTHORS_TEXT_COLS_LABELS "Имя" SEPARATOR "authorName" \
    SEPARATOR "Информация" SEPARATOR "authorInfo" \
    SEPARATOR "Дата" SEPARATOR "lastUpdate"

#define ERAS_TEXT_COLS_LABELS "Название" SEPARATOR "eraName" \
    SEPARATOR "Дата" SEPARATOR "lastUpdate"

#define ARTS_NAME_KEY "artName"
#define ARTS_AUTHORS_KEY "artAuthors"
#define ARTS_RANK_KEY "isDomestic"
#define ARTS_ERA_KEY "artEra"
#define ARTS_INFO_KEY "artInfo"
#define ARTS_DATE_KEY "lastUpdate"

#define AUTHORS_NAME_KEY "authorName"
#define AUTHORS_INFO_KEY "authorInfo"
#define AUTHORS_DATE_KEY "lastUpdate"

#define ERAS_NAME_KEY "eraName"
#define ERAS_DATE_KEY "lastUpdate"

#define ARTS_RANKS_KEY "ranks"
#define ARTS_RANKS "Отечественное искусство" SEPARATOR "1" \
    SEPARATOR "Зарубежное искусство" SEPARATOR "0"

#define DATAFILE_TITLE "Файл данных"
#define FILE_SIZE_MULT "1" SEPARATOR "1024" SEPARATOR "10240"
#define FILE_SIZE_UNIT "Б" SEPARATOR "КиБ" SEPARATOR "МиБ"

#define EDITOR_ADD_TITLE_KEY "addWindowTitle"
#define EDITOR_ADD_TITLE "Добавить..."
#define EDITOR_EDIT_TITLE_KEY "editWindowTitle"
#define EDITOR_EDIT_TITLE "Изменить..."
#define EDITOR_OPENFILE_TITLE_KEY "openFileTitle"
#define EDITOR_OPENFILE_TITLE "Выберите..."
#define EDITOR_ARTS_NAME_BOX_KEY "artNameBox"
#define EDITOR_ARTS_NAME_BOX "Название произведения искусства"
#define EDITOR_ARTS_AUTHORS_BOX_KEY "artAuthorsBox"
#define EDITOR_ARTS_AUTHORS_BOX "Авторы"
#define EDITOR_ARTS_RANK_BOX_KEY "artRankBox"
#define EDITOR_ARTS_RANK_BOX "Категория"
#define EDITOR_ARTS_ERA_BOX_KEY "artEraBox"
#define EDITOR_ARTS_ERA_BOX "Эпоха"
#define EDITOR_ARTS_INFO_BOX_KEY "artInfoBox"
#define EDITOR_ARTS_INFO_BOX "Информация"
#define EDITOR_ARTS_IMAGE_BOX_KEY "artImageBox"
#define EDITOR_ARTS_IMAGE_BOX "Изображение"
#define EDITOR_AUTHORS_NAME_BOX_KEY "authorNameBox"
#define EDITOR_AUTHORS_NAME_BOX "Имя автора"
#define EDITOR_AUTHORS_INFO_BOX_KEY "authorInfoBox"
#define EDITOR_AUTHORS_INFO_BOX "Информация"
#define EDITOR_AUTHORS_IMAGE_BOX_KEY "authorImageBox"
#define EDITOR_AUTHORS_IMAGE_BOX "Портрет"
#define EDITOR_ERAS_NAME_BOX_KEY "eraNameBox"
#define EDITOR_ERAS_NAME_BOX "Название эпохи"
#define EDITOR_ERAS_IMAGE_BOX_KEY "eraImageBox"
#define EDITOR_ERAS_IMAGE_BOX "Изображение"
#define EDITOR_TEMPLATE_BUTTON_KEY "templateButton"
#define EDITOR_TEMPLATE_BUTTON "Шаблон"
#define EDITOR_ADD_BUTTON_KEY "addButton"
#define EDITOR_ADD_BUTTON "Добавить"
#define EDITOR_EDIT_BUTTON_KEY "editButton"
#define EDITOR_EDIT_BUTTON "Изменить"
#define EDITOR_CANCEL_BUTTON_KEY "cancelButton"
#define EDITOR_CANCEL_BUTTON "Отмена"
#define EDITOR_ARTS_TEMPLATE_KEY "artTemplate"
#define EDITOR_AUTHORS_TEMPLATE_KEY "authorTemplate"
#define EDITOR_IMAGE_STYLE_KEY "imageStyle"
#define EDITOR_IMAGE_STYLE "background-color: rgb(0, 0, 0);"
#define EDITOR_ARTS_WIDTH_KEY "artWidth"
#define EDITOR_ARTS_WIDTH 700
#define EDITOR_ARTS_HEIGHT_KEY "artHeight"
#define EDITOR_ARTS_HEIGHT 600
#define EDITOR_AUTHORS_WIDTH_KEY "authorWidth"
#define EDITOR_AUTHORS_WIDTH 600
#define EDITOR_AUTHORS_HEIGHT_KEY "authorHeight"
#define EDITOR_AUTHORS_HEIGHT 400
#define EDITOR_ERAS_WIDTH_KEY "eraWidth"
#define EDITOR_ERAS_WIDTH 400
#define EDITOR_ERAS_HEIGHT_KEY "eraHeight"
#define EDITOR_ERAS_HEIGHT 400
#define EDITOR_TEMPLATE_SAVE_KEY "saveTemplate"
#define EDITOR_TEMPLATE_SAVE "Сохранить"
#define EDITOR_TEMPLATE_CLEAR_KEY "clearTemplate"
#define EDITOR_TEMPLATE_CLEAR "Очистить"
#define EDITOR_ARTS_UNIQUE_KEY "artUniqueKey"
#define EDITOR_ARTS_UNIQUE "artName"
#define EDITOR_AUTHORS_UNIQUE_KEY "authorUniqueKey"
#define EDITOR_AUTHORS_UNIQUE "authorName"
#define EDITOR_ERAS_UNIQUE_KEY "eraUniqueKey"
#define EDITOR_ERAS_UNIQUE "eraName"
#define EDITOR_ARTS_RANK_TYPE_KEY "rankType"
#define EDITOR_ARTS_RANK_TYPE "bool"
#define EDITOR_ERAS_KEY_FOR_ARTS_LIST_KEY "artEraNameKey"
#define EDITOR_ERAS_KEY_FOR_ARTS_LIST "eraName"
#define EDITOR_AUTHORS_KEY_FOR_ARTS_LIST_KEY "artAuthorNameKey"
#define EDITOR_AUTHORS_KEY_FOR_ARTS_LIST "authorName"
#define AL_ERAS_KEY_FOR_ARTS_LIST_KEY "artEraRemoveNameKey"
#define AL_ERAS_KEY_FOR_ARTS_LIST "artEra"
#define AL_AUTHORS_KEY_FOR_ARTS_LIST_KEY "artAuthorRemoveNameKey"
#define AL_AUTHORS_KEY_FOR_ARTS_LIST "artAuthors"
#define DATE_FORMAT_KEY "lastUpdateFormat"
#define DATE_FORMAT "yyyy-MM-dd"
#define WELCOME_LAST_FILE_KEY "lastFile"
#define WELCOME_LAST_PATH_KEY "lastPath"
#define WELCOME_CREATE_BUTTON_KEY "createButton"
#define WELCOME_OPEN_BUTTON_KEY "openButton"
#define WELCOME_LAST_BUTTON_KEY "lastButton"
#define WELCOME_EXIT_BUTTON_KEY "exitButton"
#define WELCOME_CREATE_BUTTON "Создать..."
#define WELCOME_OPEN_BUTTON "Открыть..."
#define WELCOME_LAST_BUTTON "Открыть "
#define WELCOME_EXIT_BUTTON "Выход"
#define MAIN_WIDTH_KEY "mainWidth"
#define MAIN_WIDTH 600
#define MAIN_HEIGHT_KEY "mainHeight"
#define MAIN_HEIGHT 400
#define AL_FILTER_BUTTON_KEY "filterButton"
#define AL_FILTER_BUTTON "Фильтр"
#define AL_FILTER_APPLY_KEY "filterApply"
#define AL_FILTER_APPLY "Применить"
#define AL_SORT_BUTTON_KEY "sortButton"
#define AL_SORT_BUTTON "Сортировка"
#define AL_SORT_ORDER_ASC_KEY "sortOrderAsc"
#define AL_SORT_ORDER_ASC "А..Я"
#define AL_SORT_ORDER_DSC_KEY "sortOrderDsc"
#define AL_SORT_ORDER_DSC "Я..А"
#define AL_ADD_BUTTON_KEY "addButton"
#define AL_ADD_BUTTON "Добавить"
#define AL_EDIT_BUTTON_KEY "editButton"
#define AL_EDIT_BUTTON "Изменить"
#define AL_DEL_BUTTON_KEY "delButton"
#define AL_DEL_BUTTON "Удалить"
#define CHOOSER_TITLE_KEY "chooseListTitle"
#define CHOOSER_TITLE "Выберите..."
#define CHOOSER_SEARCH_BOX_KEY "searchBox"
#define CHOOSER_SEARCH_BOX "Поиск"
#define CHOOSER_SEARCH_BUTTON_KEY "searchButton"
#define CHOOSER_SEARCH_BUTTON "Найти"
#define CHOOSER_DONE_BUTTON_KEY "doneButton"
#define CHOOSER_DONE_BUTTON "Выбрать"
#define CHOOSER_CANCEL_BUTTON_KEY "cancelButton"
#define CHOOSER_CANCEL_BUTTON "Отмена"
#define ML_EXPORT_TO_JSON_KEY "exportToJsonButton"
#define ML_EXPORT_TO_JSON "Экспорт в JSON"
#define ML_SAVE_BUTTON_KEY "saveButton"
#define ML_SAVE_BUTTON "Сохранить"
#define ML_MERGE_BUTTON_KEY "mergeButton"
#define ML_MERGE_BUTTON "Объеденить"
#define ERRORS_SUBSECTION_KEY "AppErrors"
#define ERRORS_TITLE_KEY "msgTitle"
#define ERRORS_TITLE "Внимание!"
#define ERRORS_FILE_ON_BASESUBDIR_KEY "fileOnBaseSubdir"
#define ERRORS_FILE_ON_BASESUBDIR "Выбранный файл находится в директории текущей базы!"
#define ERRORS_SAVE_CONFIG_KEY "saveConfig"
#define ERRORS_SAVE_CONFIG "Ошибка записи настроек программы в файл:\n"
#define ERRORS_FILE_ALREADY_EXIST_KEY "fileAlreadyExist"
#define ERRORS_FILE_ALREADY_EXIST "Файл с таким именем уже существует!"
#define ERRORS_CHECK_PREFIX_KEY "firstCheckPrefix"
#define ERRORS_CHECK_PREFIX "Заполните раздел"
#define ERRORS_ITEM_ALREADY_EXIST_KEY "itemAlreadyExist"
#define ERRORS_ITEM_ALREADY_EXIST "Такая запись уже есть!"
#define ERRORS_DATA_SAVED_KEY "dataSaved"
#define ERRORS_DATA_SAVED "Данные успешно записаны!"
#define ERRORS_DATA_UNSAVED_KEY "dataUnsaved"
#define ERRORS_DATA_UNSAVED "Ошибка записи данных в:\n"
#define ERRORS_DATA_CHANGED_KEY "saveBeforeClose"
#define ERRORS_DATA_CHANGED "Данные изменены! Сохранить?"
#define ERRORS_ALREADY_SAVED_KEY "alreadySaved"
#define ERRORS_ALREADY_SAVED "Данные уже сохранены!"
#define ERRORS_SAVE_BEFORE_KEY "saveBefore"
#define ERRORS_SAVE_BEFORE "Сначала сохраните данные!"
#define EXPORT_TITLE_KEY "exportTitle"
#define EXPORT_TITLE "Экспорт базы данных в JSON"
#define EXPORT_PREFIX_LABEL_KEY "prefixLabel"
#define EXPORT_PREFIX_LABEL "Префикс пути к файлам"
#define EXPORT_PREFIX_KEY "prefixData"
#define EXPORT_PREFIX "https://pro-prof.com/artists-puzzle/load"
#define EXPORT_SAVE_KEY "exportButton"
#define EXPORT_SAVE "Экспортировать"
#define EXPORT_CANCEL_KEY "cancelButton"
#define EXPORT_CANCEL "Отмена"
#define EXPORT_ANNOTATION_KEY "exportAnnotation"
#define EXPORT_ANNOTATION "Внимание! В директории сохранения JSON-файла будут созданы три подкаталога с файлами основных разделов"
#define EXPORT_WIDTH_KEY "width"
#define EXPORT_WIDTH 600
#define EXPORT_HEIGHT_KEY "height"
#define EXPORT_HEIGHT 200
#define EXPORT_FILE_DIALOG_TITLE_KEY "fileDialogTitle"
#define EXPORT_FILE_DIALOG_TITLE "Экспорт..."
#define EXPORT_LAST_PATH_KEY "lastPath"
#define EXPORT_LAST_PATH ""
#define ERRORS_JOBISDON_DIALOG_KEY "jobisDone"
#define ERRORS_JOBISDON_DIALOG "Данные экспортированы!"
#define JSON_EXTENSION ".json"
#define EDITOR_LAST_PATH_KEY "lastPath"
#define EDITOR_LAST_PATH ""
#define ERRORS_JOBISDONOT_DIALOG_KEY "jobisDoNot"
#define ERRORS_JOBISDONOT_DIALOG "Что-то пошло не по плану!"

#define ML_FILE_LABEL_KEY "fileLabel"
#define ML_FILE_LABEL "Файл данных"
#define ML_FILE_CREATED_LABEL_KEY "fileCreatedLabel"
#define ML_FILE_CREATED_LABEL "Создан"
#define ML_FILE_MODIFIED_LABEL_KEY "fileModifiedLabel"
#define ML_FILE_MODIFIED_LABEL "Изменен"
#define ML_FILE_SIZE_LABEL_KEY "fileSizeLabel"
#define ML_FILE_SIZE_LABEL "Размер"
#define ML_FILES_LABEL_KEY "filesLabel"
#define ML_FILES_LABEL "файл(ов)"
#define ML_FILE_DATE_FORMAT_KEY "fileDateFormat"
#define ML_FILE_DATE_FORMAT "yyyy.MM.dd HH:mm"

#define AL_SORT_ENABLE_CHECK_KEY "enableSortingCheckState"
#define AL_SORT_ENABLE_CHECK 0
#define AL_SORT_ENABLE_TITLE_KEY "enableSortingTitle"
#define AL_SORT_ENABLE_TITLE "Включить сортировку по..."

#define RESOURCE_CHECK ":/check.png"
#define RESOURCE_QUESTION ":/question.png"
#define RESOURCE_SCHEMA ":/schema.json"

#define MERGE_OPENFILE_TITLE_KEY "mergeOpenFileTitle"
#define MERGE_OPENFILE_TITLE "Выберите..."

#define ERRORS_MERGE_SAME_FILE_KEY "sameFileForMerge"
#define ERRORS_MERGE_SAME_FILE "Выбран тот же файл!"
#define ERRORS_MERGE_ITEM_ADDED_KEY "mergeItemAdded"
#define ERRORS_MERGE_ITEM_ADDED "Запись добавлена"
#define ERRORS_MERGE_ITEM_CHANGED_KEY "mergeItemChanged"
#define ERRORS_MERGE_ITEM_CHANGED "Запись обновлена"
#define ERRORS_MERGE_FILE_ADDED_KEY "mergeFileAdded"
#define ERRORS_MERGE_FILE_ADDED "Файл добавлен"
#define ERRORS_MERGE_FILE_ADD_FAIL_KEY "mergeFileAddFail"
#define ERRORS_MERGE_FILE_ADD_FAIL "Ошибка добавления файла"
#define ERRORS_MERGE_ITEM_SKIPPED_KEY "mergeItemSkipped"
#define ERRORS_MERGE_ITEM_SKIPPED "Запись пропущена"
#define ERRORS_MERGE_SUCCESS_KEY "mergeSuccess"
#define ERRORS_MERGE_SUCCESS "Объединение успешно завершено!\nХотите посмотреть лог?"
#define ERRORS_MERGE_FAIL_KEY "mergeFail"
#define ERRORS_MERGE_FAIL "Объединение завершено с ошибками!\nХотите посмотреть лог?"

#define LOG_TITLE_KEY "logTitle"
#define LOG_TITLE "Информация"

#define LOG_CLOSE_KEY "logCloseButton"
#define LOG_CLOSE "Закрыть"

#define ERRORS_MERGE_SECTION_KEY "mergeSectionTitle"
#define ERRORS_MERGE_SECTION "Объединение разделов"
#define ERRORS_INVALID_SCHEMA_KEY "invalidSchema"
#define ERRORS_INVALID_SCHEMA "Файл не соотвествует схеме!"
#define ERRORS_READ_FILE_KEY "readJson"
#define ERRORS_READ_FILE "Ошибка чтения файла. Нет доступа!"
#define ERRORS_CHECK_PATH_KEY "checkPaths"
#define ERRORS_CHECK_PATH "Ошибка проверки подкаталогов. Нет доступа!"
#define ERRORS_WRITE_FILE_KEY "writeJson"
#define ERRORS_WRITE_FILE "Ошибка записи файла. Нет доступа!"
#define ERRORS_CHECK_FILES_BEGIN_KEY "checkFileBegin"
#define ERRORS_CHECK_FILES_BEGIN "Проверка файлов..."
#define ERRORS_CHECK_FILES_SECTION_BEGIN_KEY "checkFilesSectionBegin"
#define ERRORS_CHECK_FILES_SECTION_BEGIN "Раздел"
#define ERRORS_FILE_NOT_FOUND_KEY "fileNotFound"
#define ERRORS_FILE_NOT_FOUND "Отсутствует файл"
#define ERRORS_NOT_FOUND_KEY "everythingIsNormal"
#define ERRORS_NOT_FOUND "Ошибок не найдено!"
#define ERRORS_CHECK_ARTS_BEGIN_KEY "checkArtsBegin"
#define ERRORS_CHECK_ARTS_BEGIN "Проверка произведений искусства..."
#define ERRORS_CHECK_ARTS_ERA_EMPTY_KEY "artEraEmpty"
#define ERRORS_CHECK_ARTS_ERA_EMPTY "эпоха не указана!"
#define ERRORS_CHECK_ARTS_ERA_NOT_FOUND_KEY "artEraNotFound"
#define ERRORS_CHECK_ARTS_ERA_NOT_FOUND "эпоха отсутствует"
#define ERRORS_CHECK_ARTS_AUTHORS_EMPTY_KEY "artAuthorsEmpty"
#define ERRORS_CHECK_ARTS_AUTHORS_EMPTY "авторы не указаны!"
#define ERRORS_CHECK_ARTS_AUTHOR_NOT_FOUND_KEY "artAuthorNotFound"
#define ERRORS_CHECK_ARTS_AUTHOR_NOT_FOUND "автор отсутствует"
#define ERRORS_CHECK_ARTS_INFO_EMPTY_KEY "artInfoEmpty"
#define ERRORS_CHECK_ARTS_INFO_EMPTY "информация не указана!"
#define ERRORS_CHECK_AUTHORS_BEGIN_KEY "checkAuthorsBegin"
#define ERRORS_CHECK_AUTHORS_BEGIN "Проверка авторов..."
#define ERRORS_CHECK_AUTHORS_INFO_EMPTY_KEY "authorInfoEmpty"
#define ERRORS_CHECK_AUTHORS_INFO_EMPTY "информация не указана!"

#define ERRORS_FOUND_KEY "errorsFound"
#define ERRORS_FOUND "Найдены ошибки!"
#define ERRORS_DETAILS_KEY "errorDetails"
#define ERRORS_DETAILS "Подробнее..."

enum JsonDataSections {
    ArtsSection = 0,
    AuthorsSection = 1,
    ErasSection = 2
};

#endif // DEFINES_H
