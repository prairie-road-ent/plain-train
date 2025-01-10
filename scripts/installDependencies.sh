if [ ! -d $DEPENDENCIES_DIRECTORY_PATH ]; then
    sudo mkdir -p $DEPENDENCIES_DIRECTORY_PATH
fi
sudo curl --location --remote-name https://github.com/TinyCC/tinycc/archive/refs/heads/mob.zip \
    && unzip -d $DEPENDENCIES_DIRECTORY_PATH ./mob.zip \
    && rm ./mob.zip \
    && cd $DEPENDENCIES_DIRECTORY_PATH/tinycc-mob \
    && sudo ./configure \
    && sudo make \
    && sudo make install
sudo curl --location --remote-name https://github.com/madler/zlib/releases/download/v1.2.13/zlib-1.2.13.tar.xz \
    && tar --directory $DEPENDENCIES_DIRECTORY_PATH --extract --verbose --file ./zlib-1.2.13.tar.xz \
    && rm ./zlib-1.2.13.tar.xz  \
    && cd $DEPENDENCIES_DIRECTORY_PATH/zlib-1.2.13 \
    && sudo ./configure \
    && sudo make \
    && sudo make install
sudo curl --location --remote-name https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz \
    && tar --directory $DEPENDENCIES_DIRECTORY_PATH --extract --verbose --file ./jansson-2.14.tar.gz \
    && rm ./jansson-2.14.tar.gz \
    && cd $DEPENDENCIES_DIRECTORY_PATH/jansson-2.14 \
    && sudo ./configure \
    && sudo make \
    && sudo make install