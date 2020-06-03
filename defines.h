#ifndef DEFINES_H
#define DEFINES_H

#define SEPARATOR "|"

#define APPLICATION_NAME  "LEditor"
#define APPLICATION_VERSION "0.1 alpha"

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

#define ARTS_TEXT_COLS_H "artName" SEPARATOR "isDomestic" SEPARATOR "artEra" SEPARATOR "artAuthors" SEPARATOR "artInfo"
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

#define ARTS_RANK_KEY "ranks"
#define ARTS_RANK "Отечественное искусство" SEPARATOR "0" \
    SEPARATOR "Зарубежное искусство" SEPARATOR "1"

#define LAST_PATH_KEY "lastPath"

enum JsonDataSections {
    ArtsSection = 0,
    AuthorsSection = 1,
    ErasSection = 2
};

#endif // DEFINES_H
