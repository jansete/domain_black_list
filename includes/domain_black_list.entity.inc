<?php

define('DOMAIN_BLACK_LIST_BUNDLE', 'domain_black_list_bundle');

/**
 * Implements hook_entity_info().
 */
function domain_black_list_entity_info() {
  $info['domain_black_list'] = array(
    'label' => t('Domain Black List'),
    'entity class' => 'DomainBlackList',
    'controller class' => 'DomainBlackListController',
    'base table' => 'domain_black_list',
    'fieldable' => FALSE,
    'entity keys' => array(
      'id' => 'did',
      'bundle' => 'type',
    ),
    'bundle keys' => array(
      'bundle' => 'type',
    ),
    'bundles' => array(
      DOMAIN_BLACK_LIST_BUNDLE => array(
        'label' => t('Domain Black List bundle'),
        'admin' => array(
          'path' => 'admin/config/system/domain-black-list/manage',
          'access arguments' => array(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM),
        ),
      ),
    ),
    'static cache' => TRUE,
    'load hook' => 'domain_black_list_load',
    'view modes' => array(
      'full' => array(
        'label' => t('Default'),
        'custom settings' => FALSE,
      ),
    ),
    'label callback' => 'entity_class_label',
    'module' => 'domain_black_list',
    'access callback' => 'domain_black_list_access',
  );

  return $info;
}

/**
 * Load a domain.
 */
function domain_black_list_load($did, $reset = FALSE) {
  $domains = domain_black_list_load_multiple(array($did), array(), $reset);
  return reset($domains);
}

/**
 * Load multiple domains based on certain conditions.
 */
function domain_black_list_load_multiple($dids = FALSE, $conditions = array(), $reset = FALSE) {
  return entity_load('domain_black_list', $dids, $conditions, $reset);
}

/**
 * Save domain.
 */
function domain_black_list_save($domain) {
  $domain->uid = isset($domain->uid) ? $domain->uid : 1;
  $domain->type = isset($domain->type) ? $domain->type : DOMAIN_BLACK_LIST_BUNDLE;

  $domain->changed = REQUEST_TIME;

  if (isset($domain->is_new) && $domain->is_new) {
    $domain->created = $domain->changed;
  }
  entity_save('domain_black_list', $domain);
}

/**
 * Delete single domain.
 */
function domain_black_list_delete($domain) {
  entity_delete('domain_black_list', entity_id('domain_black_list' ,$domain));
}

/**
 * Delete multiple domains.
 */
function domain_black_list_delete_multiple($dids) {
  entity_delete_multiple('domain_black_list', $dids);
}