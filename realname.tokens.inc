<?php

/**
 * @file
 * Builds placeholder replacement tokens for realname.
 */

/**
 * Implements hook_token_info().
 */
function realname_token_info() {
  $info['tokens']['user']['name-raw'] = array(
    'name' => t('Raw name'),
    'description' => t('The raw login name of the user account, unprocessed by the RealName module.'),
  );
  
  return $info;
}

/**
 * Implements hook_token_info_alter().
 */
function realname_token_info_alter(&$info) {
  // Since the [user:name] token uses format_username(), its meta-data should
  // be altered to reflect that it will be the real name.
  $info['tokens']['user']['name']['name'] = t('Real name');
  $info['tokens']['user']['name']['description'] = t('The real name of the user account.');
}

/**
 * Implements hook_tokens().
 */
function realname_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);

  if ($type == 'user' && !empty($data['user'])) {
    $account = $data['user'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'name-raw':
          $replacements[$original] = $sanitize ? check_plain($account->name) : $account->name;
          break;
      }
    }
    
    $user_fields = field_info_instances('user', 'user');
    foreach ($user_fields as $field_name => $field) {
      $token_name = strtr($field_name, '_', '-');
      if ($field['widget']['module'] == 'text' && isset($tokens[$token_name]) && !empty($account->{$field_name}[LANGUAGE_NONE][0])) {
        $original = $tokens[$token_name];
        $item = $account->{$field_name}[LANGUAGE_NONE][0];
        $instance = field_info_instance('user', $field_name, 'user');
        $replacements[$original] = $sanitize ? _text_sanitize($instance, LANGUAGE_NONE, $item, 'value') : $item['value'];
      }
    }
  }

  return $replacements;
}
