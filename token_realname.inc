<?php
// $Id$ */
/**
* @file
*   Token module support for the realname module.
*/

function realname_token_list($type = 'all') {
  $tokens = array();
//  if ($type == 'user' || $type == 'node' || $type == 'all' || $type == 'global') {
    $prefix = 'user-';
    if ($type == 'comment') {
      $prefix = 'comment-';
    }
    $tokens[$type][$prefix .'realname'] = t('The RealName for the user.');
    $tokens[$type][$prefix .'realname-link'] = t('Themed username link.');
    $tokens[$type][$prefix .'homepage'] = t('The home page for the user.');
    return $tokens;
//  }
}

function realname_token_values($type, $object = NULL, $options = array()) {
  global $user;
  $tokens = array();
//  if ($type == 'user' || $type == 'node' || $type == 'all' || $type == 'global') {
    if (!$object) {
      $object = $user;
    }
    $prefix = 'user-';
    if ($type == 'comment') {
      $prefix = 'comment-';
    }
    $tokens[$prefix .'realname'] = realname_make_name($object);
    $tokens[$prefix .'realname-link'] = theme('username', $object);
    $tokens[$prefix .'homepage'] = $object->homepage;
    return $tokens;
//  }
}
