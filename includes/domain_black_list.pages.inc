<?php

/**
 * Returns a render array with all domains entities.
 * @todo Add pager
 */
function domain_black_list_basic_list_entities() {
  $content = array();
  // Load all of our entities.
  $entities = domain_black_list_load_multiple();
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      // Create tabular rows for our entities.
      $rows[] = array(
        'data' => array(
          'id' => $entity->did,
          'domain' => $entity->domain,
          'status' => $entity->status,
          'edit_link' => l(t('edit'), DOMAIN_BLACK_LIST_ADMIN_PATH . '/domain/' . $entity->did . '/edit'),
          'delete_link' => l(t('delete'), DOMAIN_BLACK_LIST_ADMIN_PATH. '/domain/' . $entity->did . '/delete'),
        ),
      );
    }
    // Put our entities into a themed table.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(
        t('ID'),
        t('Domain'),
        t('Status'),
        t('Edit Link'),
        t('Delete Link')
      ),
    );
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No domains currently exist.'),
    );
  }
  return $content;
}

/**
 *  Callback for example 3: Show message if feature is disabled. Redirect to
 *  content edit form to test it.
 */
function domain_black_list_example_3_page() {
  drupal_set_message(t('Write a domain in the body, fill other fields and click in submit button.'));
  if (!variable_get('domain_black_list_field_validation')) {
    DomainBlackListFilter::showDisableFeatureMessage();
  }

  // @todo check if content type exist else redirect to configuration page
  drupal_goto('node/add/article');
}