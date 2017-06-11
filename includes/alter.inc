<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see drupal_render()
 * @see theme()
 */

/**
 * Implements hook_css_alter().
 */
function uikit_admin_css_alter(&$css) {
  $uikit_admin = drupal_get_path('theme', 'uikit_admin') . '/css';

  // Stop Drupal core stylesheets from being loaded.
  unset($css[drupal_get_path('module', 'system') . '/system.admin.css']);

  // Stop dblog stylesheet from being loaded.
  unset($css[drupal_get_path('module', 'dblog') . '/dblog.css']);

  $vertical_tabs = 'misc/vertical-tabs.css';
  $vertical_tabs_rtl = 'misc/vertical-tabs-rtl.css';
  if (isset($css[$vertical_tabs])) {
    $css[$vertical_tabs]['data'] = $uikit_admin . '/vertical-tabs.css';
  }
  if (isset($css[$vertical_tabs_rtl])) {
    $css[$vertical_tabs_rtl]['data'] = $uikit_admin . '/vertical-tabs-rtl.css';
  }

  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    $css['misc/ui/jquery.ui.theme.css']['data'] = $uikit_admin . '/jquery.ui.theme.css';
  }
}

/**
 * Implements hook_element_info_alter().
 */
function uikit_admin_element_info_alter(&$type) {
  if (isset($type['machine_name'])) {
    $type['machine_name']['#process'] = array(
      'ajax_process_form',
      'uikit_admin_process_machine_name',
    );
  }
}

/**
 * Implements hook_form_alter().
 */
function uikit_admin_form_alter(&$form, &$form_state) {
  // Drupal core is pretty good at putting form buttons into an actions element.
  // This isn't always the case, and many contributed modules dont' do this as
  // well. This will move form buttons into an actions element for proper
  // themeing.
  $no_actions = !isset($form['actions']) && isset($form['submit']);
  if ($no_actions) {
    $form['actions'] = array(
      '#type' => 'actions',
      '#attributes' => array(
        'class' => array('uk-admin-clearfix'),
      ),
    );

    foreach ($form as $key => $item) {
      $submit = is_array($item) && isset($item['#type']) && $item['#type'] == 'submit';
      $button = is_array($item) && isset($item['#type']) && $item['#type'] == 'button';

      if ($submit || $button) {
        $form['actions'][$key] = $form[$key];
        unset($form[$key]);
      }
    }
  }

  foreach ($form as $key => $item) {
    if (is_array($item) && isset($item['#type'])) {
      $types = array(
        'actions',
        'hidden',
        'token',
      );

      // Hidden and action elements do not receive the uk-form-row class when
      // themed. This will add the class for proper themeing.
      if (in_array($item['#type'], $types)) {
        $form[$key]['#attributes']['class'][] = 'uk-form-row';
      }
    }
    elseif (is_array($item) && isset($item['#markup'])) {
      // Add a wrapper with the uk-form-row class to markup elements for proper
      // themeing.
      $form[$key]['#prefix'] = '<div class="uk-form-row">';
      $form[$key]['#suffix'] = '</div>';
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for filter_admin_format_form().
 */
function uikit_admin_form_filter_admin_format_form_alter(&$form, &$form_state) {
  // Add the uk-form-row class to the enabled filters prefix so the proper
  // margin is added.
  $prefix = $form['filters']['status']['#prefix'];
  $form['filters']['status']['#prefix'] = str_replace('">', '" class="uk-form-row">', $prefix);
}

/**
 * Implements hook_form_FORM_ID_alter() for views_ui_edit_form().
 */
function uikit_admin_form_views_ui_edit_form_alter(&$form, &$form_state) {
  $form['changed']['#attributes'] = array(
    'class' => array('view-changed', 'uk-alert', 'uk-alert-warning', 'js-hide', 'uk-margin-remove'),
  );
  $form['displays']['#prefix'] = '<h1 class="unit-title uk-margin-remove uk-text-bold">' . t('Displays') . '</h1><div class="views-displays">';
}

/**
 * Implements hook_js_alter().
 */
function uikit_admin_js_alter(&$javascript) {
  $uikit_admin = drupal_get_path('theme', 'uikit_admin') . '/js';

  $autocomplete = 'misc/autocomplete.js';
  if (isset($javascript[$autocomplete])) {
    $javascript[$autocomplete]['data'] = $uikit_admin . '/autocomplete.js';
  }

  $block = drupal_get_path('module', 'block') . '/block.js';
  if (isset($javascript[$block])) {
    $javascript[$block]['data'] = $uikit_admin . '/block.js';
  }

  $dashboard = drupal_get_path('module', 'dashboard') . '/dashboard.js';
  if (isset($javascript[$dashboard])) {
    $javascript[$dashboard]['data'] = $uikit_admin . '/dashboard.js';
  }

  $machine_name = 'misc/machine-name.js';
  if (isset($javascript[$machine_name])) {
    $javascript[$machine_name]['data'] = $uikit_admin . '/machine-name.js';
  }

  $module_filter = drupal_get_path('module', 'module_filter') . '/js/module_filter.js';
  if (isset($javascript[$module_filter])) {
    $javascript[$module_filter]['data'] = $uikit_admin . '/module_filter.js';
  }

  $tabledrag = 'misc/tabledrag.js';
  if (isset($javascript[$tabledrag])) {
    $javascript[$tabledrag]['data'] = $uikit_admin . '/tabledrag.js';
  }

  $text = drupal_get_path('module', 'text') . '/text.js';
  if (isset($javascript[$text])) {
    $javascript[$text]['data'] = $uikit_admin . '/text.js';
  }

  $textarea = 'misc/textarea.js';
  if (isset($javascript[$textarea])) {
    $javascript[$textarea]['data'] = $uikit_admin . '/textarea.js';
  }

  $views_admin = drupal_get_path('module', 'views') . '/js/views-admin.js';
  if (isset($javascript[$views_admin])) {
    //$javascript[$views_admin]['data'] = $uikit_admin . '/views-admin.js';

    // Views administration pages do not work with jQuery 2+. So we need to
    // remove the jQuery, jQuery Migrate and UIkit javascript libraries. We also
    // Remove the UIkit base theme overrides.js and UIkit Admin's
    // uikit-admin.js, otherwise we end up conflicting with View's behaviors.
    unset($javascript['//cdnjs.cloudflare.com/ajax/libs/jquery/2.1.4/jquery.min.js']);
    unset($javascript['//cdnjs.cloudflare.com/ajax/libs/jquery-migrate/1.4.1/jquery-migrate.min.js']);
    unset($javascript['//cdnjs.cloudflare.com/ajax/libs/uikit/2.27.2/js/uikit.min.js']);
    unset($javascript['sites/localhost.uikit-7.x-2.x/themes/contrib/uikit/uikit_core/js/overrides.js']);
    unset($javascript[$uikit_admin . '/uikit-admin.js']);

    // Add UIkit Admin's uikit-admin.views.css stylesheet for basic styling
    // overrides on Views administration pages.
    drupal_add_css(drupal_get_path('theme', 'uikit_admin') . '/css/uikit-admin.views.css');
  }

  $views_ajax = drupal_get_path('module', 'views') . '/js/ajax.js';
  if (isset($javascript[$views_ajax])) {
    $javascript[$views_ajax]['data'] = $uikit_admin . '/ajax.js';
  }
}

/**
 * Implements hook_menu_local_tasks_alter().
 */
function uikit_admin_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  // Define various icons.
  $plus = '<i class="uk-icon-plus"></i> ';

  $action_paths = array(
    'admin/reports/updates/install',
  );

  foreach ($data['actions']['output'] as $key => $action) {
    $path = isset($action['#link']['path']) ? $action['#link']['path'] : $action['#link']['href'];
    preg_match('/(shortcut.*)\/add-link/', $path, $matches);
    $shortcut_add_link = isset($matches[0]) && $matches[0] == 'shortcut/%/add-link';

    // Add icon for any shorcut add link path.
    if ($shortcut_add_link) {
      $title = $plus . $data['actions']['output'][$key]['#link']['title'];
      $data['actions']['output'][$key]['#link']['title'] = $title;
      $data['actions']['output'][$key]['#link']['localized_options']['html'] = TRUE;
    }
    elseif (in_array($path, $action_paths)) {
      $title = $plus . $data['actions']['output'][$key]['#link']['title'];
      $data['actions']['output'][$key]['#link']['title'] = $title;
      $data['actions']['output'][$key]['#link']['localized_options']['html'] = TRUE;
    }
  }
}
