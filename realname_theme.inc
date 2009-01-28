<?php
// $Id$

/**
 * @file
 *   This include file intercepts the theme('username'... function
 *   and uses the RealName instead of the username.
 *
 * @copyright Copyright (c) 2007-2008 Nancy Wichmann.  All rights reserved.
 */
/**
 * Format a username.  (copied from theme.inc)
 *
 * @param $object
 *   The user object to format, usually returned from user_load().
 * @return
 *   A string containing an HTML link to the user's page if the passed object
 *   suggests that this is a site user. Otherwise, only the username is returned.
 */
function phptemplate_username($object) {
  // If we have a user id but no realname, then make one.
  if ($object->uid && empty($object->realname) && user_access('use realname')) {
    $object->realname = realname_make_name($object);
  }

  if ($object->uid && $object->realname) {
    // Shorten the name when it is too long or it will break many tables.
    $max_name = variable_get('realname_max_username', 20);
    if (drupal_strlen($object->realname) > $max_name) {
      $name = drupal_substr($object->realname, 0, $max_name - 3) .'...';
    }
    else {
      $name = $object->realname;
    }

    if (user_access('access user profiles')) {
      $attrs = array();
      if (isset($object->homepage)) {
        $url = $object->homepage;
        $title = t("View user's home page.");
        if (variable_get('realname_nofollow', FALSE)) {
          $attrs['rel'] = 'nofollow';
        }
      }
      else {
        $url = 'user/'. $object->uid;
        $title = t('View user profile.');
      }
      $attrs['title'] = $title;
      $output = l($name, $url, array('attributes' => $attrs));
    }
    else {
      $output = check_plain($name);
    }
  }
  elseif ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if ($object->homepage) {
      $output = l($object->name, $object->homepage, array('attributes' => array('title' => t("View user's home page."))));
    }
    else {
      $output = check_plain($object->name);
    }

    if (variable_get('realname_notver', TRUE)) {
      $output .= ' ('. t('not verified') .')';
    }
  }
  else {
    $output = variable_get('anonymous', t('Anonymous'));
  }

  return $output;
}
