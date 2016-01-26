<?php

define('ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM', 'administer domains black list entities');
define('CREATE_DOMAINS_BLACK_LIST_ENTITIES_PERM', 'create domains black list entities');
define('EDIT_ANY_DOMAINS_BLACK_LIST_ENTITIES_PERM', 'edit any domains black list entities');
define('DELETE_ANY_DOMAINS_BLACK_LIST_ENTITIES_PERM', 'delete any domains black list entities');

/**
 * Implements hook_permission().
 */
function domain_black_list_permission() {
  return array(
    ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM => array(
      'title' => t('Administer domains black list entities'),
      'description' => t('Allows users to configure domains black list entities.'),
      'restrict access' => TRUE,
    ),
    CREATE_DOMAINS_BLACK_LIST_ENTITIES_PERM => array(
      'title' => t('Create domains black list entities'),
      'description' => t('Allows users to create domains.'),
      'restrict access' => TRUE,
    ),
    EDIT_ANY_DOMAINS_BLACK_LIST_ENTITIES_PERM => array(
      'title' => t('Edit any domains black list entities'),
      'description' => t('Allows users to edit any domains.'),
      'restrict access' => TRUE,
    ),
    DELETE_ANY_DOMAINS_BLACK_LIST_ENTITIES_PERM => array(
      'title' => t('Delete domains black list entities'),
      'description' => t('Allows users to delete domains.'),
      'restrict access' => TRUE,
    ),
  );
}

/**
 * Access callback for domain.
 */
function domain_black_list_access($op, $domain, $account = NULL, $entity_type = NULL) {
  global $user;

  if (!isset($account)) {
    $account = $user;
  }
  switch ($op) {
    case 'create':
      return user_access(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM, $account)
      || user_access(CREATE_DOMAINS_BLACK_LIST_ENTITIES_PERM, $account);
    case 'edit':
      return user_access(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM, $account)
      || user_access(EDIT_ANY_DOMAINS_BLACK_LIST_ENTITIES_PERM, $account);
    case 'delete':
      return user_access(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM, $account)
      || user_access(DELETE_ANY_DOMAINS_BLACK_LIST_ENTITIES_PERM, $account);
  }
}