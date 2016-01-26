<?php

define('DOMAIN_BLACK_LIST_ADMIN_PATH', 'admin/config/system/domain-black-list/manage');

/**
 * Implements hook_menu().
 */
function domain_black_list_menu() {
  $path = drupal_get_path('module', 'domain_black_list');
  $include_path = $path . '/includes';
  $items = array();

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH] = array(
    'title' => 'Administer Domains Black List',
    'page callback' => 'domain_black_list_basic_list_entities',
    'access arguments' => array(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM),
    'file' => 'domain_black_list.pages.inc',
    'file path' => $include_path,
  );

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/domain/add'] = array(
    'title' => 'Add an Domain Black List Entity',
    'page callback' => 'domain_black_list_add',
    'access arguments' => array(CREATE_DOMAINS_BLACK_LIST_ENTITIES_PERM),
    'type' => MENU_LOCAL_ACTION,
    'file' => 'domain_black_list.forms.inc',
    'file path' => $include_path,
  );

  $domain_uri = 'domain/%domain_black_list';

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/'. $domain_uri . '/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('domain_black_list_form', 6),
    'access callback' => 'entity_access',
    'access arguments' => array('edit', 'domain_black_list', 6),
    'file' => 'domain_black_list.forms.inc',
    'file path' => $include_path,
    'type' => MENU_LOCAL_TASK,
    'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
  );

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/'. $domain_uri . '/delete'] = array(
    'title' => 'Delete Domain',
    'title callback' => 'domain_black_list_label',
    'title arguments' => array(6),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('domain_black_list_delete_form', 6),
    'access callback' => 'entity_access',
    'access arguments' => array('delete', 'domain_black_list', 6),
    'file' => 'domain_black_list.forms.inc',
    'file path' => $include_path,
  );

  return $items;
}