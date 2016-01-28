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

  // List of all entity_example_basic entities.
  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => 1,
  );

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/settings'] = array(
    'title' => 'Settings',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('domain_black_list_settings_form', 6),
    'access arguments' => array(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM),
    'file' => 'domain_black_list.forms.inc',
    'file path' => $include_path,
    'type' => MENU_LOCAL_TASK,
    'weight' => 2,
  );

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/example-1'] = array(
    'title' => 'Example 1',
    'page callback' => 'theme',
    'page arguments' => array('dbl_example_1'),
    'access arguments' => array(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM),
    'type' => MENU_LOCAL_TASK,
    'weight' => 3,
  );

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/example-2'] = array(
    'title' => 'Example 2',
    'page callback' => 'theme',
    'page arguments' => array('dbl_example_2'),
    'access arguments' => array(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM),
    'type' => MENU_LOCAL_TASK,
    'weight' => 4,
  );

  $items[DOMAIN_BLACK_LIST_ADMIN_PATH . '/example-3'] = array(
    'title' => 'Example 3',
    'page callback' => 'domain_black_list_example_3_page',
    'access arguments' => array(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM),
    'file' => 'domain_black_list.pages.inc',
    'file path' => $include_path,
    'type' => MENU_LOCAL_TASK,
    'weight' => 5,
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