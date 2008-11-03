<?php
// $Id$
/**
 * @file
 * Realname module support for Profile (core) module.
 */

function realname_profile_get_fields($current) {
  $fields = $links = array();
  $result = db_query("SELECT * FROM {profile_fields}");
  while ($field = db_fetch_array($result)) {
    switch ($field['type']) {
      case 'textfield':
        $name = $field['name'];
        $selected = array_key_exists($name, $current);
        $fields[$name] = array(
          'title' => $field['title'],
          'weight' => $selected ? $current[$name] : 0,
          'selected' => $selected,
          );
        break;

      case 'url':
        $links[$field['name']] = $field['title'];
        break;

      default:
        break;
    }
  }
  return array('fields' => $fields, 'links' => $links);
}
