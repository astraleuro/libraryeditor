#ifndef DEFINES_H
#define DEFINES_H

#define SEPARATOR "|"

#define APPLICATION_NAME  "LEditor"
#define APPLICATION_VERSION "0.1 alpha"

#define PROGRAM_AUTHOR_NAME "Кирилл Зимин (astral.euro@gmail.com)"
#define PROGRAM_NAME APPLICATION_NAME " - управление данными приложения «Пазлы-Живопись»\n" \
    "Версия: " APPLICATION_VERSION "\n" "Автор: " PROGRAM_AUTHOR_NAME

#define MAINWINDOW_TITLE APPLICATION_NAME " " APPLICATION_VERSION

#define CONFIG_FILE APPLICATION_NAME ".conf"

#define BASE_EXTENSION ".ledb"
#define BASE_EXTENSION_FILTER "*" BASE_EXTENSION
#define IMAGE_EXTENSION_FILTER "*.jpg, *.png"

#define OPENFILE_TITLE "Открыть..."
#define SAVEFILE_TITLE "Сохранить..."

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
#define ARTS_RANKS "Отечественное искусство" SEPARATOR "0" \
    SEPARATOR "Зарубежное искусство" SEPARATOR "1"

#define DATAFILE_TITLE "Файл данных"
#define FILE_SIZE_MULT 1024
#define FILE_SIZE_UNIT "KB"

#define EDITOR_ADD_TITLE_KEY "addWindowTitle"
#define EDITOR_ADD_TITLE "Добавить..."
#define EDITOR_EDIT_TITLE_KEY "editWindowTitle"
#define EDITOR_EDIT_TITLE "Изменить..."

#define EDITOR_OPENFILE_TITLE_KEY "openFileTitle"
#define EDITOR_OPENFILE_TITLE "Изменить..."

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
#define AL_SORT_APPLY_KEY "sortApply"
#define AL_SORT_APPLY "Применить"
#define AL_SORT_ORDER_ASC_KEY "sortOrderAsc"
#define AL_SORT_ORDER_ASC "А..Я"
#define AL_SORT_ORDER_DSC_KEY "sortOrderDsc"
#define AL_SORT_ORDER_DSC "Я..А"

#define AL_ADD_BUTTON_KEY "addButton"
#define AL_ADD_BUTTON "Добавить"
#define AL_SAVE_BUTTON_KEY "saveButton"
#define AL_SAVE_BUTTON "Сохранить"
#define AL_EDIT_BUTTON_KEY "editButton"
#define AL_EDIT_BUTTON "Изменить"
#define AL_DEL_BUTTON_KEY "delButton"
#define AL_DEL_BUTTON "Удалить"

#define EDITOR_TEMPLATE_SAVE_KEY "saveTemplate"
#define EDITOR_TEMPLATE_SAVE "Сохранить"
#define EDITOR_TEMPLATE_CLEAR_KEY "clearTemplate"
#define EDITOR_TEMPLATE_CLEAR "Очистить"

#define EDITOR_ERAS_KEY_FOR_ARTS_LIST_KEY "artEraNameKey"
#define EDITOR_ERAS_KEY_FOR_ARTS_LIST "eraName"
#define EDITOR_AUTHORS_KEY_FOR_ARTS_LIST_KEY "artAuthorNameKey"
#define EDITOR_AUTHORS_KEY_FOR_ARTS_LIST "authorName"

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

#define ERRORS_SUBSECTION_KEY "AppErrors"

#define ERRORS_TITLE_KEY "msgTitle"
#define ERRORS_TITLE "Внимание!"

#define ERRORS_FILE_ON_BASESUBDIR_KEY "fileOnBaseSubdir"
#define ERRORS_FILE_ON_BASESUBDIR "Выбранный файл находится в директории текущей базы!"

#define ERRORS_SAVE_CONFIG_KEY "saveConfig"
#define ERRORS_SAVE_CONFIG "Ошибка сохранения настроек программы в файл:\n"

//#define ERRORS_
//#define ERRORS_

//#define ERRORS_
//#define ERRORS_

//#define ERRORS_
//#define ERRORS_


#define RESOURCE_QUESTION ":/question.png"

enum JsonDataSections {
    ArtsSection = 0,
    AuthorsSection = 1,
    ErasSection = 2
};

#endif // DEFINES_H
