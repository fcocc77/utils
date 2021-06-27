
size=128

svg_to_png() {
    path=$1
    svg=$2
    suffix=$3
    color=$4

    filename=$(basename $svg)
    filename=${filename::-4}

    svg_temp="$path/$filename"_temp_.svg
    output="$path/$filename"_"$suffix".png

    if [ ! -f $output ]; then
        cp $svg $svg_temp

        # cambia el color 'fill'
        svg_temp
        sed -i "s|fill=\"none\"|fill=\"$color\"|g" $svg_temp
        sed -i "s|fill:none|fill:$color|g" $svg_temp
        sed -i "s|stroke:none|stroke:$color|g" $svg_temp
        #

        # cambia tamaño
        sed -i "s|height=\"24px\"|height=\"$size\"|g" $svg_temp
        sed -i "s|width=\"24px\"|width=\"$size\"|g" $svg_temp

        sed -i "s|height=\"24\"|height=\"$size\"|g" $svg_temp
        sed -i "s|width=\"24\"|width=\"$size\"|g" $svg_temp
        #
        #

        inkscape $svg_temp -e $output

        rm $svg_temp
    fi

}
