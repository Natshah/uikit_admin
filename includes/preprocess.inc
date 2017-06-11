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
  drupal_add_css('//fonts.googleapis.com/css?family=Open+Sans:300,400,600,700', array(
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

  $variables['overlay'] = in_array('overlay', $variables['page']['#theme_wrappers']);
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
  $submit = isset($variables['element']['#submit']) ? $variables['element']['#submit'] : array();
  $views_add_display = in_array('views_ui_edit_form_submit_add_display', $submit);
  $views_edit_view = in_array('views_ui_edit_view_form_cancel', $submit) || in_array('views_ui_edit_view_form_submit', $submit);

  if ($views_add_display) {
    $variables['theme_hook_suggestions'][] = 'button__views_add_display';
  }
  elseif ($views_edit_view) {
    $variables['theme_hook_suggestions'][] = 'button__views_edit_view';
    $variables['element']['#attributes']['class'] = array('uk-button');

    switch ($variables['element']['#value']) {
      case 'Save':
        $variables['element']['#attributes']['class'][] = 'uk-button-primary';
        break;

      case 'Cancel':
        $variables['element']['#attributes']['class'][] = 'uk-button-danger';
        break;
    }
  }
  else {
    $variables['element']['#attributes']['class'] = array('uk-button');

    switch ($variables['element']['#value']) {
      case 'Add':
      case 'Apply':
      case 'Continue':
      case 'Create new account':
      case 'Create new set':
      case 'Create new style':
      case 'Download these updates':
      case 'Install':
      case 'Revert':
      case 'Save':
      case 'Save block':
      case 'Save blocks':
      case 'Save configuration':
      case 'Save content type':
      case 'Save permissions':
      case 'Save role':
      case 'Save settings':
      case 'Save field settings':
      case 'Upload':
      case 'Update effect':
      case 'Update preview':
      case 'Update style':
        $variables['element']['#attributes']['class'][] = 'uk-button-primary';
        break;

      case 'Override defaults':
      case 'Preview':
        $variables['element']['#attributes']['class'][] = 'uk-button-warning';
        break;

      case 'Delete':
      case 'Delete content type':
      case 'Delete role':
      case 'Remove':
        $variables['element']['#attributes']['class'][] = 'uk-button-danger';
        break;
    }
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_container().
 */
function uikit_admin_preprocess_container(&$variables) {
  $element = $variables['element'];
  $edit_view_page = fnmatch('admin/structure/views/view/*/edit', current_path());

  if ($edit_view_page) {
    $save_cancel_container = isset($element['save']) && isset($element['cancel']);
    if ($save_cancel_container) {
      $variables['theme_hook_suggestions'][] = 'container__views_view_edit';
    }
  }

  if (isset($element['#attributes']['class']) && is_array($element['#attributes']['class'])) {
    $help_block = in_array('uk-form-help-block', $element['#attributes']['class']);

    if ($help_block) {
      if(($key = array_search('uk-form-row', $element['#attributes']['class'])) !== false) {
        unset($variables['element']['#attributes']['class'][$key]);
      }
    }
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_fieldset().
 */
function uikit_admin_preprocess_fieldset(&$variables) {
  $element = $variables['element'];
  $parents = $element['#parents'];
  $edit_view_page = fnmatch('admin/structure/views/ajax/*', current_path());

  if ($edit_view_page) {
    $variables['theme_hook_suggestions'] = array('fieldset__views_fieldset');
  }
  else {
    $non_collapsible = array(
      'admin_theme',
    );

    $group_fieldset = isset($element['#group_fieldset']) && $element['#group_fieldset'];

    if (!$group_fieldset) {
      $variables['theme_hook_suggestions'] = array('fieldset__collapsible');
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
}

/**
 * Implements template_preprocess_HOOK() for theme_form().
 */
function uikit_admin_preprocess_form(&$variables) {
  $variables['element']['#attributes']['class'] = array();
  $element = $variables['element'];
  $form_id = $element['#form_id'];

  $horizontal_forms = array(
    'node_admin_content',
    'user_filter_form',
  );

  if (in_array($form_id, $horizontal_forms)) {
    $variables['element']['#attributes']['class'][] = 'uk-form';
    $variables['element']['#attributes']['class'][] = 'uk-form-horizontal';
  }
  else {
    $variables['element']['#attributes']['class'][] = 'uk-form';
    $variables['element']['#attributes']['class'][] = 'uk-form-stacked';
  }

  if ($form_id == 'views_ui_preview_form') {
    $variables['element']['#attributes']['class'][] = 'uk-form';
    $variables['element']['#attributes']['class'][] = 'uk-clearfix';
  }
  if ($form_id == 'views_ui_config_item_form') {
    $variables['element']['#attributes']['class'] = array();
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_form_element().
 */
function uikit_admin_preprocess_form_element(&$variables) {
  $edit_view_page = fnmatch('admin/structure/views/ajax/*', current_path());
  $variables['element']['#wrapper_attributes']['class'][] = 'form-item';

  if ($edit_view_page) {
    $variables['theme_hook_suggestions'] = array('form_element__views_form_element');
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_form_element_label().
 */
function uikit_admin_preprocess_form_element_label(&$variables) {
  $edit_view_page = fnmatch('admin/structure/views/ajax/*', current_path());
  $element = $variables['element'];
  $type = $element['#type'];
  $children = $element['#children'];

  if ($type == 'item' && empty($children)) {
    $variables['theme_hook_suggestions'] = array('form_element_label__item');
  }

  if ($edit_view_page) {
    $variables['theme_hook_suggestions'] = array('form_element_label__views_form_element_label');
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_item_list().
 */
function uikit_admin_preprocess_item_list(&$variables) {
  $variables['attributes']['class'][] = 'uk-margin-top';
}

/**
 * Implements template_preprocess_HOOK() for theme_link().
 */
function uikit_admin_preprocess_link(&$variables) {
  $attributes = $variables['options']['attributes'];
  $id = isset($attributes['id']) ? $variables['options']['attributes']['id'] : 0;
  $edit_cancel = $id && $id == 'edit-cancel';

  if ($edit_cancel) {
    $classes = isset($attributes['class']) ? $attributes['class'] : array();

    if (empty($classes) || !in_array('uk-button', $classes)) {
      $variables['options']['attributes']['class'][] = 'uk-button';
    }
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_links__ctools_dropbutton().
 */
function uikit_admin_preprocess_links__ctools_dropbutton(&$variables) {
  $variables['attributes']['class'][] = 'uk-list';
  $variables['attributes']['class'][] = 'uk-margin-remove';
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
 * Implements template_preprocess_overlay().
 */
function uikit_admin_preprocess_overlay(&$variables) {
  if (module_exists('shortcut') && shortcut_set_edit_access() && path_is_admin(current_path())) {
    $variables['title_suffix']['add_or_remove_shortcut'] = _uikit_admin_shortcut_add_or_remove_link();
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
 * Implements hook_preprocess_HOOK() for system-themes-page.tpl.php.
 */
function uikit_admin_preprocess_system_themes_page(&$variables) {
  $theme_groups = $variables['theme_groups'];
  $variables['themes'] = array();

  foreach ($variables['theme_group_titles'] as $state => $title) {
    $variables['themes'][$state] = array();

    foreach ($theme_groups[$state] as $key => $theme) {
      $variables['themes'][$state][$key] = array(
        'name' => $theme->info['name'],
      );

      // Style theme info.
      $variables['themes'][$state][$key]['description'] = $theme->info['description'];
      $variables['themes'][$state][$key]['name'] .= isset($theme->info['version']) ? ' ' . $theme->info['version'] : '';
      $variables['themes'][$state][$key]['name'] .= count($theme->notes) ? ' (' . implode(', ', $theme->notes) . ')' : '';

      if ($state == 'enabled') {
        $screenshot_variables = array(
          'path' => $theme->screenshot['path'],
          'width' => '294',
          'alt' => $theme->screenshot['alt'],
          'title' => $theme->screenshot['title'],
          'attributes' => array(
            'class' => array('screenshot', 'uk-thumbnail', 'uk-float-left', 'uk-margin-right'),
          ),
        );

        // Theme the screenshot.
        $variables['themes'][$state][$key]['screenshot'] = $theme->screenshot ? theme('image', $screenshot_variables) : '<div class="no-screenshot">' . t('no screenshot') . '</div>';

        $variables['themes'][$state][$key]['incompatibility'] = FALSE;
        $variables['themes'][$state][$key]['links'] = array();

        // Make sure to provide feedback on compatibility.
        if (!empty($theme->incompatible_core)) {
          $variables['themes'][$state][$key]['incompatibility'] = t('This version is not compatible with Drupal !core_version and should be replaced.', array('!core_version' => DRUPAL_CORE_COMPATIBILITY));
        }
        elseif (!empty($theme->incompatible_php)) {
          if (substr_count($theme->info['php'], '.') < 2) {
            $theme->info['php'] .= '.*';
          }
          $variables['themes'][$state][$key]['incompatibility'] = t('This theme requires PHP version @php_required and is incompatible with PHP version !php_version.', array(
            '@php_required' => $theme->info['php'],
            '!php_version' => phpversion(),
          ));
        }
        else {
          $variables['themes'][$state][$key]['links'] = theme('links', array(
            'links' => $theme->operations,
            'attributes' => array(
              'class' => array(
                'uk-subnav',
                'uk-subnav-line',
                'uk-margin-remove',
                'uk-admin-theme-operations',
              ),
            ),
          ));
        }
      }
      else {
        $screenshot_variables = array(
          'path' => $theme->screenshot['path'],
          'alt' => $theme->screenshot['alt'],
          'title' => $theme->screenshot['title'],
          'attributes' => array(
            'class' => array('screenshot'),
          ),
        );

        // Theme the screenshot.
        $variables['themes'][$state][$key]['screenshot'] = $theme->screenshot ? theme('image', $screenshot_variables) : '<div class="no-screenshot">' . t('no screenshot') . '</div>';

        $variables['themes'][$state][$key]['incompatibility'] = FALSE;
        $variables['themes'][$state][$key]['links'] = array();

        // Make sure to provide feedback on compatibility.
        if (!empty($theme->incompatible_core)) {
          $variables['themes'][$state][$key]['incompatibility'] = t('This version is not compatible with Drupal !core_version and should be replaced.', array('!core_version' => DRUPAL_CORE_COMPATIBILITY));
        }
        elseif (!empty($theme->incompatible_php)) {
          if (substr_count($theme->info['php'], '.') < 2) {
            $theme->info['php'] .= '.*';
          }
          $variables['themes'][$state][$key]['incompatibility'] = t('This theme requires PHP version @php_required and is incompatible with PHP version !php_version.', array(
            '@php_required' => $theme->info['php'],
            '!php_version' => phpversion(),
          ));
        }
        else {
          $variables['themes'][$state][$key]['links'] = theme('links', array(
            'links' => $theme->operations,
            'attributes' => array(
              'class' => array(
                'uk-subnav',
                'uk-subnav-line',
                'uk-margin-remove',
                'uk-admin-theme-operations',
              ),
            ),
          ));
        }
      }
    }
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_table().
 */
function uikit_admin_preprocess_table(&$variables) {
  $variables['attributes']['class'][] = 'uk-table-hover';
  $variables['attributes']['class'][] = 'uk-table-striped';
  $variables['attributes']['class'][] = 'uk-table-middle';

  $id = isset($variables['attributes']['id']) ? $variables['attributes']['id'] : 0;

  if ($id && $id == 'admin-dblog') {
    $variables['theme_hook_suggestions'][] = 'table__dblog';
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_textfield().
 */
function uikit_admin_preprocess_textfield(&$variables) {
  $element = $variables['element'];
  $array_parents = isset($element['#array_parents']) ? $element['#array_parents'] : array();
  $edit_view_page = fnmatch('admin/structure/views/ajax/*', current_path());

  if (!$edit_view_page) {
    if (in_array('error_page', $array_parents) || in_array('site_frontpage', $array_parents)) {
      $variables['element']['#attributes']['class'][] = 'uk-margin-small-left';
    }

    $variables['element']['#attributes']['class'][] = 'uk-form-width-large';
  }

  if ($element['#autocomplete_path'] && !empty($element['#autocomplete_input'])) {
    $variables['theme_hook_suggestions'][] = 'textfield__autocomplete';
  }
}

/**
 * Implements template_preprocess_HOOK() for views-view-table.tpl.php.
 */
function uikit_admin_preprocess_views_view_table(&$variables) {
  $classes = array('uk-table');
  $variables['attributes_array']['class'] = $classes;
}
