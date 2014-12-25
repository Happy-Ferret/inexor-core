#!/bin/bash
set -ev

echo "branch: ${TRAVIS_BRANCH}, Job No: ${TRAVIS_JOB_NUMBER}" #e.g. "branch: master, Job No: 251.4"

if [[ ${TRAVIS_JOB_NUMBER} != *1 && ${TRAVIS_JOB_NUMBER} != *5 ]]; then #just deploy one build for windows and one for linux
    exit 0 #do not display as failure
fi

cd $TRAVIS_BUILD_DIR

export BUILD_NAME="$(echo "${TRAVIS_BRANCH}-${TRAVIS_JOB_NUMBER}-${TRAVIS_COMMIT}-" | sed 's#/#-#')-$([[ ${TRAVIS_JOB_NUMBER} != *5 ]] && echo linux || echo windows)"
#e.g. master-251.5-10240128410510-linux

if [ "${TRAVIS_BRANCH}" == "master" ] 
then # the master-nightly-build has the data-folder included
    git clone --depth 1 https://github.com/inexor-game/data.git nightly
    rm -rf ./nightly/.git*
else
    mkdir nightly
fi

cp -r ./bin_* nightly
cp ./inexor_unix nightly
cp ./inexor.bat nightly
zip -r ${BUILD_NAME}.zip nightly
sha512sum ${BUILD_NAME}.zip > ${BUILD_NAME}.zip.sum
echo "sending ${BUILD_NAME}.zip"
curl --connect-timeout 1800 --ftp-create-dirs -T "${BUILD_NAME}.zip" -u $FTP_USER:$FTP_PASSWORD ftp://inexor.org/
curl --ftp-create-dirs -T "${BUILD_NAME}.zip.sum" -u $FTP_USER:$FTP_PASSWORD ftp://inexor.org/

exit 0