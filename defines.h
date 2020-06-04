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

#define OPENFILE_TITLE "Открыть..."
#define SAVEFILE_TITLE "Сохранить..."

#define MSGBOX_TITLE "Внимание!"
#define MSG_SETTINGS_WRITE_ERROR "Ошибка записи настроек программы в файл:\n"

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
#define TEXT_COLS_F_KEY "textFooterCols"

#define ARTS_TEXT_COLS_H "artName" SEPARATOR "artAuthors" SEPARATOR "artEra" SEPARATOR "isDomestic" SEPARATOR "artInfo"
#define ARTS_TEXT_COLS_F "lastUpdate"

#define AUTHORS_TEXT_COLS_H "authorName" SEPARATOR "authorInfo"
#define AUTHORS_TEXT_COLS_F "lastUpdate"

#define ERAS_TEXT_COLS_H "eraName" SEPARATOR "eraInfo"
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
    SEPARATOR "Информация" SEPARATOR "eraInfo" \
    SEPARATOR "Дата" SEPARATOR "lastUpdate"

#define ARTS_AUTHORS_KEY_NAME "artAuthors"
#define ARTS_RANK_KEY_NAME "isDomestic"

#define ARTS_RANKS_KEY "ranks"
#define ARTS_RANKS "Отечественное искусство" SEPARATOR "0" \
    SEPARATOR "Зарубежное искусство" SEPARATOR "1"

#define LAST_PATH_KEY "lastPath"

#define DATAFILE_TITLE "Файл данных"
#define FILE_SIZE_MULT 1024
#define FILE_SIZE_UNIT "KB"

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
#define EDITOR_AUTHOR_NAME_BOX_KEY "authorNameBox"
#define EDITOR_AUTHOR_NAME_BOX "Имя автора"
#define EDITOR_AUTHOR_INFO_BOX_KEY "authorInfoBox"
#define EDITOR_AUTHOR_INFO_BOX "Информация"
#define EDITOR_ERAS_NAME_BOX_KEY "eraNameBox"
#define EDITOR_ERAS_NAME_BOX "Название эпохи"
#define EDITOR_ERAS_INFO_BOX_KEY "eraInfoBox"
#define EDITOR_ERAS_INFO_BOX "Информация"
#define EDITOR_ADD_TITLE_KEY "editorAddTitle"
#define EDITOR_ADD_TITLE "Добавление..."
#define EDITOR_EDIT_TITLE_KEY "editorEditTitle"
#define EDITOR_EDIT_TITLE "Изменение..."
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
#define EDITOR_ERAS_TEMPLATE_KEY "eraTemplate"

enum JsonDataSections {
    ArtsSection = 0,
    AuthorsSection = 1,
    ErasSection = 2
};

#endif // DEFINES_H
