<?php
// $Id$ */
/**
* @file
*   Token module support for the realname module.
*/

function realname_token_list($type = 'all') {
  if ($type == 'user' || $type == 'node' || $type == 'all' || $type == 'global') {
    $tokens[$type]['realname'] = t('The RealName for the user.');
    $tokens[$type]['realname-link'] = t('Themed username link.');
    $tokens[$type]['homepage'] = t('The home page for the user.');
    return $tokens;
  }
}

function realname_token_values($type, $object = NULL, $options = array()) {
  global $user;
  if ($type == 'user' || $type == 'node' || $type == 'all' || $type == 'global') {
    if (!$object) {
      $object = $user;
    }
    $tokens['realname'] = realname_make_name($object);
    $tokens['realname-link'] = theme('username', $object);
    $tokens['homepage'] = $object->homepage;    
    return $tokens;
  }
}
