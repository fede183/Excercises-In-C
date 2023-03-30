echo "echo Restoring environment" > "/home/federico/Documents/Projects/Exercises-In-C/SFML Projects/template/build/build/Release/generators/deactivate_conanrunenv-release-x86_64.sh"
for v in ALSA_CONFIG_DIR
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "/home/federico/Documents/Projects/Exercises-In-C/SFML Projects/template/build/build/Release/generators/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "/home/federico/Documents/Projects/Exercises-In-C/SFML Projects/template/build/build/Release/generators/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export ALSA_CONFIG_DIR="/home/federico/.conan2/p/libale1f75d2a3a991/p/res/alsa"