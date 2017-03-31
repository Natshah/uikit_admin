<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * @see process.inc
 */

/**
 * Implements template_preprocess_html().
 */
function uikit_admin_preprocess_html(&$variables) {
  // Retrieve the Font Mfizz for technology icons.
  // NOTE: You can use uk-icon-* and uk-text-* classes to make these icons match
  // the styles of UIkit/Font Awesome icons you use in your sub-theme.
  // See http://fizzed.com/oss/font-mfizz for usage and available icons.
  drupal_add_css('//cdnjs.cloudflare.com/ajax/libs/font-mfizz/2.4.1/font-mfizz.css', array(
    'type' => 'external',
    'group' => CSS_THEME,
    'every_page' => TRUE,
    'weight' => -10,
    'version' => '2.4.1',
  ));

  // Retrieve the Open Sans font from Google fonts.
  drupal_add_css('//fonts.googleapis.com/css?family=Open+Sans:300,400,600', array(
    'type' => 'external',
    'group' => CSS_THEME,
    'every_page' => TRUE,
    'weight' => -10,
  ));
}

/**
 * Implements template_preprocess_page().
 */
function uikit_admin_preprocess_page(&$variables) {
  $variables['primary_local_tasks'] = $variables['tabs'];
  unset($variables['primary_local_tasks']['#secondary']);

  $variables['secondary_local_tasks'] = array(
    '#theme' => 'menu_local_tasks',
    '#secondary' => $variables['tabs']['#secondary'],
  );

  if (module_exists('shortcut') && shortcut_set_edit_access() && path_is_admin(current_path())) {
    $variables['title_suffix']['add_or_remove_shortcut'] = _uikit_admin_shortcut_add_or_remove_link();
  }
}

/**
 * Implements template_preprocess_block().
 */
function uikit_admin_preprocess_block(&$variables) {
  $region = $variables['block']->region;

  if ($region == 'dashboard_main' || $region == 'dashboard_sidebar') {
    $variables['title_attributes_array']['class'][] = 'uk-panel-title';
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_button().
 */
function uikit_admin_preprocess_button(&$variables) {
  $variables['element']['#attributes']['class'] = array('uk-button');

  switch ($variables['element']['#value']) {
    case 'Add':
    case 'Continue':
    case 'Create new set':
    case 'Download these updates':
    case 'Save':
    case 'Save block':
    case 'Save blocks':
    case 'Save configuration':
    case 'Save content type':
    case 'Save role':
    case 'Save settings':
    case 'Save field settings':
    case 'Upload':
      $variables['element']['#attributes']['class'][] = 'uk-button-primary';
      break;

    case 'Preview':
      $variables['element']['#attributes']['class'][] = 'uk-button-warning';
      break;

    case 'Cancel':
    case 'Delete':
    case 'Delete content type':
    case 'Delete role':
      $variables['element']['#attributes']['class'][] = 'uk-button-danger';
      break;
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_fieldset().
 */
function uikit_admin_preprocess_fieldset(&$variables) {
  $element = $variables['element'];
  $parents = $element['#parents'];

  $non_collapsible = array(
    'admin_theme',
  );

  $group_fieldset = isset($element['#group_fieldset']) && $element['#group_fieldset'];

  if (!$group_fieldset) {
    $variables['theme_hook_suggestions'] = array('fieldset');
    $variables['element']['#attributes'] = array('class' => array('uk-form-row'));
  }

  foreach ($parents as $parent) {
    if (in_array($parent, $non_collapsible)) {
      $variables['theme_hook_suggestions'] = array('fieldset__non_collapsible');
      $help = isset($variables['element']['help']);
      $guidelines = isset($variables['element']['guidelines']);

      if ($help && $guidelines) {
        $variables['element']['#attributes']['class'][] = 'uk-panel';
        $variables['element']['#attributes']['class'][] = 'uk-panel-box';
        $variables['element']['#attributes']['class'][] = 'uk-margin-remove';
      }
      break;
    }
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_form().
 */
function uikit_admin_preprocess_form(&$variables) {
  $variables['element']['#attributes']['class'] = array('uk-form');
  $form_id = $variables['element']['#form_id'];

  $horizontal_forms = array(
    'node_admin_content',
    'user_filter_form',
  );

  if (in_array($form_id, $horizontal_forms)) {
    $variables['element']['#attributes']['class'][] = 'uk-form-horizontal';
  }
  else {
    $variables['element']['#attributes']['class'][] = 'uk-form-stacked';
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_form_element().
 */
function uikit_admin_preprocess_form_element(&$variables) {
  $variables['element']['#wrapper_attributes']['class'][] = 'form-item';
}

/**
 * Implements template_preprocess_HOOK() for theme_form_element_label().
 */
function uikit_admin_preprocess_form_element_label(&$variables) {
  $element = $variables['element'];
  $type = $element['#type'];
  $children = $element['#children'];

  if ($type == 'item' && empty($children)) {
    $variables['theme_hook_suggestions'] = array('form_element_label__item');
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_item_list().
 */
function uikit_admin_preprocess_item_list(&$variables) {
  $variables['attributes']['class'][] = 'uk-margin-top';
}

/**
 * Implements template_preprocess_HOOK() for theme_menu_local_tasks().
 */
function uikit_admin_preprocess_menu_local_tasks(&$variables) {
  global $theme_key;
  $secondary_style = theme_get_setting('secondary_tasks_style', $theme_key);

  switch ($secondary_style) {
    case '0':
    case 'uk-subnav-line':
      $variables['secondary_attributes_array']['class'][] = 'uk-margin-remove';
      break;

    case 'uk-subnav-pill':
      $variables['secondary_attributes_array']['class'][] = 'uk-margin-small-top';
      break;
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_status_report().
 */
function uikit_admin_preprocess_status_report(&$variables) {
  $requirements = $variables['requirements'];

  $general_information = array(
    'drupal' => array(),
    'cron' => array(),
    'web_server' => array(),
    'php' => array(),
    'database' => array(),
  );

  $general_information['drupal']['install_profile'] = '<em>Standard profile</em>';

  $grouped_requirements = array(
    'info' => array(),
    'ok' => array(),
    'warning' => array(),
    'error' => array(),
  );

  $status_counters = array(
    'checked' => array(
      'count' => 0,
      'title' => t('Checked'),
    ),
    'error' => array(
      'count' => 0,
    ),
    'warning' => array(
      'count' => 0,
    ),
    'grid_width' => 'uk-width-1-1',
  );

  foreach ($requirements as $key => $requirement) {
    $severity = isset($requirement['severity']) ? $requirement['severity'] : (int) 0;
    $title = $requirement['title'];

    $ignored = array(
      'Drupal',
      'Install profile',
      'Cron maintenance tasks',
      'Web server',
      'PHP',
      'PHP memory limit',
      'Database system version',
      'Database system',
    );

    // REQUIREMENT_INFO (-1).
    if ($severity == REQUIREMENT_INFO) {
      $status_counters['checked']['count']++;

      if (!in_array($title, $ignored)) {
        $grouped_requirements['info'][] = $requirement;
      }
    }

    // REQUIREMENT_OK (0).
    if ($severity == REQUIREMENT_OK) {
      $status_counters['checked']['count']++;

      if (!in_array($title, $ignored)) {
        $grouped_requirements['ok'][] = $requirement;
      }
    }

    // REQUIREMENT_WARNING (1).
    if ($severity == REQUIREMENT_WARNING) {
      $status_counters['checked']['count']++;
      $status_counters['warning']['count']++;
      $grouped_requirements['warning'][] = $requirement;
      unset($variables['requirements'][$key]);
    }

    // REQUIREMENT_ERROR (2).
    if ($severity == REQUIREMENT_ERROR) {
      $status_counters['checked']['count']++;
      $status_counters['error']['count']++;
      $grouped_requirements['error'][] = $requirement;
      unset($variables['requirements'][$key]);
    }

    if ($title == 'Drupal') {
      $general_information['drupal']['version'] = $requirement['value'];
      unset($variables['requirements'][$key]);
    }
    elseif ($title == 'Install profile') {
      $general_information['drupal']['install_profile'] = $requirement['value'];
      unset($variables['requirements'][$key]);
    }
    elseif ($title == 'Cron maintenance tasks') {
      $last_cron = time() - variable_get('cron_last');

      if ($last_cron < 86400) {
        $general_information['cron']['last_cron'] = 'uk-admin-last-cron-less-day';
      }
      elseif ($last_cron >= 86400 && $last_cron < 604800) {
        $general_information['cron']['last_cron'] = 'uk-admin-last-cron-week';
      }
      elseif ($last_cron >= 604800) {
        $general_information['cron']['last_cron'] = 'uk-admin-last-cron-over-week';
      }

      $run_cron = '/admin/reports/status/run-cron';
      $more_information = '/admin/config/system/cron';
      $general_information['cron']['last_run'] = $requirement['value'];
      $general_information['cron']['run_cron'] = l(t('@text', array('@text' => 'Run cron')), $run_cron, array('attributes' => array('class' => array('uk-button', 'uk-button-primary'))));
      $general_information['cron']['more_information'] = l(t('@text', array('@text' => 'more information')), $more_information);
      unset($variables['requirements'][$key]);
    }
    elseif ($title == 'Web server') {
      $apache = substr($requirement['value'], 0, 6) === 'Apache';
      $nginx = substr($requirement['value'], 0, 5) === 'nginx';

      if ($apache) {
        $general_information['web_server']['icon'] = 'icon-apache';
      }
      elseif ($nginx) {
        $general_information['web_server']['icon'] = 'icon-nginx';
      }
      else {
        $general_information['web_server']['icon'] = 'uk-icon-server uk-text-muted';
      }

      $general_information['web_server']['value'] = $requirement['value'];
      unset($variables['requirements'][$key]);
    }
    elseif ($title == 'PHP') {
      $general_information['php']['version'] = $requirement['value'];
      unset($variables['requirements'][$key]);
    }
    elseif ($title == 'PHP memory limit') {
      $general_information['php']['memory_limit'] = $requirement['value'];
      unset($variables['requirements'][$key]);
    }
    elseif ($title == 'Database system version') {
      $general_information['database']['version'] = $requirement['value'];
      unset($variables['requirements'][$key]);
    }
    elseif ($title == 'Database system') {
      $general_information['database']['system'] = $requirement['value'];
      unset($variables['requirements'][$key]);
    }
  }

  // Assign error/warning titles based on plurality of error/warning counts.
  $status_counters['error']['title'] = $status_counters['error']['count'] == 1 ? t('Error') : t('Errors');
  $status_counters['warning']['title'] = $status_counters['warning']['count'] == 1 ? t('Warning') : t('Warnings');

  if ($status_counters['error']['count'] && $status_counters['warning']['count']) {
    $status_counters['grid_width'] = 'uk-width-small-1-1 uk-width-medium-1-3';
  }
  elseif ($status_counters['error']['count'] || $status_counters['warning']['count']) {
    $status_counters['grid_width'] = 'uk-width-small-1-1 uk-width-medium-1-2';
  }

  $variables['errors'] = $status_counters['error']['count'];
  $variables['warnings'] = $status_counters['warning']['count'];
  $variables['general_information'] = $general_information;
  $variables['grouped_requirements'] = $grouped_requirements;
  $variables['status_counters'] = $status_counters;
}

/**
 * Implements template_preprocess_HOOK() for theme_table().
 */
function uikit_admin_preprocess_table(&$variables) {
  $variables['attributes']['class'][] = 'uk-table-hover';
  $variables['attributes']['class'][] = 'uk-table-striped';

  $id = isset($variables['attributes']['id']) ? $variables['attributes']['id'] : 0;

  if ($id && $id == 'admin-dblog') {
    $variables['theme_hook_suggestions'][] = 'table__dblog';
  }
}
