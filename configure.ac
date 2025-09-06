#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([idj-2025-2], [0.0.0], [])
AC_CONFIG_SRCDIR([src/base/mensagens/Canal.hpp]) # Checagem só pra ver se selecionou o diretório correto
AC_CONFIG_HEADERS([src/autoconf.h])

# Checks for programs.
AC_PROG_CXX_C_O
AC_PROG_MAKE_SET
AC_CHECK_TOOL([OBJCOPY], [objcopy])
AC_PATH_PROG([ZFLATE], [zlib-flate])

# Checks for libraries.
AC_CHECK_LIB([SDL3], [SDL_Init], [], [echo "SDL é estritamente necessário para esse projeto.";exit -1])
AC_CHECK_LIB([z], [deflate], [LIBS="-lz $LIBS"; Z=1])
if [[[ "$Z" && "${ZFLATE}" ]]];then
    echo "##############################################################"
    echo "#ZLIB e ZFLATE encontrados! Usando compressão para os assets.#"
    echo "##############################################################"
    AC_DEFINE([ASSETS_COMPRIMIDOS],[1],[Assets comprimidos])
fi

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])

# Configura os headers de assets
echo "Configurando header de assets binários..."
echo "//Header gerado automaticamente">src/assets.hpp
echo "#ifndef H_ASSETS">>src/assets.hpp
echo "#define H_ASSETS">>src/assets.hpp
echo "namespace IDJ::ASSETS{">>src/assets.hpp
for file in $(find assets -type f); do
    prefixo="_binary_$(echo $file | sed -e 's@/@_@g' -e 's@[^a-zA-Z0-9_]@@g' -e 's@\.@_@g')"
    echo "Encontrado" $prefixo
    echo "extern \"C\" char ${prefixo}_start[[]];">>src/assets.hpp
    echo "extern \"C\" char ${prefixo}_end[[]];">>src/assets.hpp
done
echo "}">>src/assets.hpp
echo "#endif">>src/assets.hpp

AC_OUTPUT
