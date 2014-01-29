#!/bin/bash
# hostname and path configuration

# back-end server domains for ssh access
: ${XWALK_STG_BACKEND:=stg-sites.vlan14.01.org}
: ${XWALK_LIVE_BACKEND:=sites1.vlan14.01.org}

# staging and live website domains
: ${XWALK_STG_HOST:=stg.crosswalk-project.org}
: ${XWALK_LIVE_HOST:=crosswalk-project.org}

# web site to fetch REVISION/PRIOR-REVISION files from
: ${XWALK_STG_WEB:=https://$XWALK_STG_HOST}
: ${XWALK_LIVE_WEB:=https://$XWALK_LIVE_HOST}

# the user:group to chown files to so Apache can write to the directories
: ${XWALK_APACHE_USER:=wwwrun}
: ${XWALK_APACHE_GROUP:=www}

# the user:group to chown files to so the site can be sync'ed from git
# by the scripts
: ${XWALK_SCRIPTS_USER:=drush}
: ${XWALK_SCRIPTS_GROUP:=users}

# XWALK_SSH_USER can also be set, to the user who should be
# used to log in to back-end servers; if not set, the current user
# will be used

# XWALK_LIVE_DOCROOT and XWALK_STG_DOCROOT can also be set (absolute path
# to Apache docroot for live and staging respectively), which
# will override the output from get_doc_root()

# get the doc root for a site; accepts one argument, which will
# be "live" or "staging"; can be overridden by env variables
function get_doc_root () {
    case $1 in
    live)
        if [ -z "$XWALK_LIVE_DOCROOT" ] ; then
            docroot=/srv/www/${XWALK_LIVE_HOST}/docroot
        else
            docroot=$XWALK_LIVE_DOCROOT
        fi
        ;;
    staging)
        if [ -z "$XWALK_STG_DOCROOT" ] ; then
            docroot=/srv/www/${XWALK_STG_HOST}/docroot
        else
            docroot=$XWALK_STG_DOCROOT
        fi
        ;;
    "")
        return 1
        ;;
    esac

    echo $docroot
    return 0
}

# show current configuration
function show_config () {
    staging_docroot=$(get_doc_root staging)
    live_docroot=$(get_doc_root live)

cat << EOF

Site configuration (variable names in brackets can be used
to override defaults):

  Staging backend (\$XWALK_STG_BACKEND): ${XWALK_STG_BACKEND}
  Live backend (\$XWALK_LIVE_BACKEND): ${XWALK_LIVE_BACKEND}

  Staging host (\$XWALK_STG_HOST): ${XWALK_STG_HOST}
  Live host (\$XWALK_LIVE_HOST): ${XWALK_LIVE_HOST}

  Staging website (\$XWALK_STG_WEB): ${XWALK_STG_WEB}
  Live website (\$XWALK_LIVE_WEB): ${XWALK_LIVE_WEB}

  Staging docroot (\$XWALK_STG_DOCROOT): ${staging_docroot}
  Live docroot (\$XWALK_LIVE_DOCROOT): ${live_docroot}

  SSH user (\$XWALK_SSH_USER): ${XWALK_SSH_USER}

  Apache user (\$XWALK_APACHE_USER): ${XWALK_APACHE_USER}
  Apache user's group (\$XWALK_APACHE_GROUP): ${XWALK_APACHE_GROUP}

  Scripts user: (\$XWALK_SCRIPTS_USER): ${XWALK_SCRIPTS_USER}
  Scripts user: (\$XWALK_SCRIPTS_GROUP): ${XWALK_SCRIPTS_GROUP}

EOF
}
