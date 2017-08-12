#
# Vremenar
# Copyright (C) 2017 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

LANGUAGES = sl_SI

# parameters: var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

TRANSLATIONS_QRC = $$top_srcdir/resources/i18n/i18n.qrc
TRANSLATIONS = $$prependAll(LANGUAGES, $$top_srcdir/resources/i18n/, .ts)

# Update and generate translations
qtPrepareTool(LRELEASE, lrelease)

lcopyqrc.input = TRANSLATIONS_QRC
lcopyqrc.output = ${QMAKE_FILE_BASE}.qrc
lcopyqrc.commands = $(COPY_DIR) ${QMAKE_FILE_IN} ${QMAKE_FILE_BASE}.qrc
lcopyqrc.CONFIG += no_link target_predeps

lrelease.input = TRANSLATIONS
lrelease.output = ${QMAKE_FILE_BASE}.qm
lrelease.commands = $$LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_BASE}.qm
lrelease.CONFIG += no_link target_predeps

QMAKE_EXTRA_COMPILERS += lcopyqrc lrelease
